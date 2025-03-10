#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ImageGauge.h"
#include "DigitalGaugeController.h"
#include "QTimer"
#include "semaphore.h"
#include "globals.h"
#include "LogWidgetController.h"
#include "packetProtocol.h"
#include <vector>
#include <mutex>
#include <thread>
#include <csignal>
#include "RPMProvider.h"
#include "HolleyCANDecoder.h"
#include "interactiveshell.h"
#include "AlarmEngine.h"
#include "SettingsHandler.h"
#include "canThread.h"
#include "timeout_manager.h"
#include "gps.h"
#include "DigitalInputIndicator.h"
#include <QtVirtualKeyboard/QVirtualKeyboardInputContext>
#include <QGuiApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "ButtonInputWidget.h"
extern "C" {
#include "syslog.h"
}

#define IAC_CAN_ADDRESS 0x9E06900A
#define BATTERY_VOLTAGE_ADDRESS 0x9E08500A
#define RPM_ADDRESS 0x9E00500A
#define COOLANT_TEMP_ADDRESS 0x9E07D00A
#define INJECTOR_DUTY_CYCLE_ADDRESS 0x9E00D00A
#define THROTTLE_POSITION_ADDRESS 0x9E07500A
#define MAP_ADDRESS 0x9E07100A
#define OIL_PRESSURE_ADDRESS 0x9E08900A
#define KNOCK_LEVEL_ADDRESS 0x9E06100A
#define KNOCK_RETARD_ADDRESS 0x9E05D00A
#define INTAKE_AIR_TEMP_ADDRESS 0x9E07900A

using namespace std;

void packetHandlerThread();
void IOThread();
void canListenerThread(SettingsHandler *settingsHandler);
int writeCANFrame(struct can_frame &frame);
void canProcessorThread();
void alarmThread();
void GPSThread();

sem_t gaugeDataSemaphore;
gaugeData currentGaugeData;

ImageGauge *coolantGauge = nullptr;
ImageGauge *oilPressureGauge = nullptr;
ImageGauge *fuelLevelGauge = nullptr;
ImageGauge *leftTurnSignal = nullptr;
ImageGauge *rightTurnSignal = nullptr;
ImageGauge *headlights = nullptr;
ImageGauge *highbeams = nullptr;
ImageGauge *speedgauge = nullptr;
DigitalGaugeController *digitalGauge1 = nullptr;
DigitalGaugeController *digitalGauge2 = nullptr;
DigitalGaugeController *digitalGauge3 = nullptr;
LogWidgetController *logWidget = nullptr;
RPMProvider rpmProvider;
InteractiveShell *shell = nullptr;
AlarmEngine *alarmEngine = nullptr;
DigitalInputIndicator *acCompressorEnabledIndicator = nullptr;
DigitalInputIndicator *accusumpEnabledIndicator = nullptr;
DigitalInputIndicator *coolingFansEnabledIndicator = nullptr;
DigitalInputIndicator *reverseLockoutOverride = nullptr;
CanIOInputHandler canIOInputHandler;
InputButton *testButton1 = nullptr;

float batteryVoltage = -1.0f;
float rpm = -1.0f;
float coolantTemperature = -1.0f;
float injectorDutyCycle = -1.0f;
float throttlePosition = -1.0f;
float map = -1.0f;
float oilPressure = -1.0f;
float oilPressureOhms = -1.0;
float knockLevel = -1.0f;
float knockRetard = -1.0f;
float airIntakeTemperature = -1.0f;
float oilTemperatureOhms = -1.0f;
float oilTemperatureTempF;
float iacPosition = -1.0f;
float rawVehicleSpeed = 0.0f;

void printAllWidgetIDs(QObject *parent){
    if(!parent) return;
    const QList<QObject*> children = parent->children();
    for (QObject *child : children) {
        QString objectName = child->objectName();
        QString className = child->metaObject()->className();

        // Print the class name and object name (if set)
        if (!objectName.isEmpty()) {
            qDebug() << "Class:" << className << ", Object Name:" << objectName;
        } else {
            qDebug() << "Class:" << className << ", Object Name: (not set)";
        }

        // Recursively call this function for each child
        printAllWidgetIDs(child);
    }
}

int initializeGauges(QQmlApplicationEngine *engine){
    //Initialize gaugeData Semaphore
    sem_init(&gaugeDataSemaphore, 0, 1);
    sem_post(&gaugeDataSemaphore);

    //Setup Coolant Gauge
    QObject *rootObject = engine->rootObjects().first();
    printAllWidgetIDs(rootObject);
    coolantGauge = rootObject->findChild<ImageGauge*>("coolantGauge");
    if(!coolantGauge){
        return -1;
    }
    coolantGauge->setImagePrefix("/home/dbertsch/images/CoolantGauge");
    coolantGauge->setMinValue(0, 0);
    coolantGauge->setMaxValue(150, 1799);
    coolantGauge->setNumImages(1799);
    coolantGauge->setValue(0);
    //Setup Oil Pressure Gauge
    oilPressureGauge = rootObject->findChild<ImageGauge*>("oilPressureGauge");
    if(!oilPressureGauge){
        return -1;
    }
    oilPressureGauge->setImagePrefix("/home/dbertsch/images/oilGauge_");
    oilPressureGauge->setMinValue(0, 0);
    oilPressureGauge->setMaxValue(150, 1799);
    oilPressureGauge->setNumImages(1799);
    oilPressureGauge->setValue(0);
    //Setup Fuel Level Gauge
    fuelLevelGauge = rootObject->findChild<ImageGauge*>("fuelGauge");
    if(!fuelLevelGauge){
        return -1;
    }
    fuelLevelGauge->setImagePrefix("/home/dbertsch/images/FuelGauge");
    fuelLevelGauge->setMinValue(0,0);
    fuelLevelGauge->setMaxValue(100, 1799);
    fuelLevelGauge->setNumImages(1799);
    fuelLevelGauge->setValue(0);
    //Setup speedometer
    speedgauge = rootObject->findChild<ImageGauge*>("speedometer");
    if(!speedgauge){
        return -1;
    }
    speedgauge->setImagePrefix("/home/dbertsch/images/SpeedGauge");
    speedgauge->setMinValue(0, 0);
    speedgauge->setMaxValue(150, 151);
    speedgauge->setNumImages(151);
    speedgauge->setValue(0);

    //Setup Turn Signal Gauges
    leftTurnSignal = rootObject->findChild<ImageGauge*>("leftTurnSignal");
    if(!leftTurnSignal){
        return -1;
    }
    leftTurnSignal->setImagePrefix("/home/dbertsch/images/arrow_left_solid.png");
    leftTurnSignal->setValue(1);

    rightTurnSignal = rootObject->findChild<ImageGauge*>("rightTurnSignal");
    if(!rightTurnSignal){
        return -1;
    }
    rightTurnSignal->setImagePrefix("/home/dbertsch/images/arrow_right_solid.png");
    rightTurnSignal->setValue(1);

    headlights = rootObject->findChild<ImageGauge*>("headlights");
    if(!headlights){
        return -1;
    }
    headlights->setImagePrefix("/home/dbertsch/images/light_low_beam.png");
    headlights->setValue(1);

    highbeams = rootObject->findChild<ImageGauge*>("highbeams");
    if(!highbeams){
        return -1;
    }
    highbeams->setImagePrefix("/home/dbertsch/images/light_high_beam.png");
    highbeams->setValue(1);

    //Setup Digital Gauges
    digitalGauge1 = rootObject->findChild<DigitalGaugeController*>("digitalGauge1");
    if(!digitalGauge1){
        return -1;
    }
    digitalGauge1->setUnit("PSI");
    digitalGauge1->setGaugeName("Oil Pressure");

    digitalGauge2 = rootObject->findChild<DigitalGaugeController*>("digitalGauge2");
    if(!digitalGauge2){
        return -1;
    }
    digitalGauge2->setUnit("  F");
    digitalGauge2->setGaugeName("Oil Temp");

    digitalGauge3 = rootObject->findChild<DigitalGaugeController*>("digitalGauge3");
    if(!digitalGauge3){
        return -1;
    }
    digitalGauge3->setUnit("Volts");
    digitalGauge3->setGaugeName("Battery Volt.");
    //Setup log widget
    logWidget = rootObject->findChild<LogWidgetController*>("logWidget");
    if(!logWidget){
        return -1;
    }
    logWidget->setFontSize(8);
    //Setup Digital Input Indicators
    acCompressorEnabledIndicator = rootObject->findChild<DigitalInputIndicator*>("digInput1");
    acCompressorEnabledIndicator->setInputName("A/C");
    if(!acCompressorEnabledIndicator){
        return -1;
    }
    acCompressorEnabledIndicator->setOnClickListener([](){
        float value = canIOInputHandler.getValue(1234, 2);
        //flip the value
        if(value < 0.5){
            printf("Setting A/C Compressor to ON\r\n");
            acCompressorEnabledIndicator->setIsOn(true);
            value = 1.0;
        }else{
            printf("Setting A/C Compressor to OFF\r\n");
            acCompressorEnabledIndicator->setIsOn(false);
            value = 0.0;
        }
        canIOInputHandler.setValue(1234, 2, value, CanIOInputHandler::valueType::INPUT);
    });
    accusumpEnabledIndicator = rootObject->findChild<DigitalInputIndicator*>("digInput2");
    if(!accusumpEnabledIndicator){
        return -1;
    }
    accusumpEnabledIndicator->setInputName("Accusump");
    //Set the onclick listener for the accusump indicator
    accusumpEnabledIndicator->setOnClickListener([](){
        float value = canIOInputHandler.getValue(1234, 1);
        //flip the value
        if(value < 0.5){
            printf("Setting Accusump to ON\r\n");
            accusumpEnabledIndicator->setIsOn(true);
            value = 1.0;
        }else{
            printf("Setting Accusump to OFF\r\n");
            accusumpEnabledIndicator->setIsOn(false);
            value = 0.0;
        }
        canIOInputHandler.setValue(1234, 1, value, CanIOInputHandler::valueType::INPUT);
    });
    coolingFansEnabledIndicator = rootObject->findChild<DigitalInputIndicator*>("digInput3");
    if(!coolingFansEnabledIndicator){
        return -1;
    }
    coolingFansEnabledIndicator->setInputName("Cooling Fans");
    coolingFansEnabledIndicator->setIsOn(true);

    reverseLockoutOverride = rootObject->findChild<DigitalInputIndicator*>("digInput4");
    if(!reverseLockoutOverride){
        return -1;
    }
    reverseLockoutOverride->setInputName("Rev Lockout");
    if(!reverseLockoutOverride){
        return -1;
    }
    reverseLockoutOverride->setOnClickListener([](){
        float value = canIOInputHandler.getValue(1234, 3);
        //flip the value
        if(value < 0.5){
            printf("Setting Reverse Lockout Override to ON\r\n");
            reverseLockoutOverride->setIsOn(true);
            value = 1.0;
        }else{
            printf("Setting Reverse Lockout Override to OFF\r\n");
            reverseLockoutOverride->setIsOn(false);
            value = 0.0;
        }
        canIOInputHandler.setValue(1234, 3, value, CanIOInputHandler::valueType::INPUT);
    });
    return 0;
}
int testCount = 0;
int acquireGaugeData(gaugeData *data){
    data->batteryVoltage = batteryVoltage;
    data->oilPressure = oilPressure;
    data->coolantTemperature = coolantTemperature;
    data->injectorDutyCycle = injectorDutyCycle + ((float)rand() / (float)RAND_MAX * 0.5);
    data->RPM = rpm;
    data->vehicleSpeed = rawVehicleSpeed;
    leftTurnSignal->setValue(!input0);//!input2
    rightTurnSignal->setValue(!input1);//!input1
    highbeams->setValue(!input2);//!input3
    headlights->setValue(!input3);//!input0
}
void setThreadName(std::thread& th, const char* threadName) {
    auto handle = th.native_handle();
    pthread_setname_np(handle, threadName);
}

int main(int argc, char *argv[])
{
    //Open syslog
    openlog("CamaroDashboardV2", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "Starting CamaroDashboardV2");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    // Print environment variables for debugging
    qDebug() << "Environment Variables:";
    qDebug() << "DISPLAY:" << qgetenv("DISPLAY");
    qDebug() << "QT_IM_MODULE:" << qgetenv("QT_IM_MODULE");
    const QUrl url(QStringLiteral("qrc:/qt/qml/Main/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    //Register Custom Widgets
    qmlRegisterType<ImageGauge>("com.example1", 1, 0, "ImageGauge");
    qmlRegisterType<DigitalGaugeController>("com.example2", 1, 0, "DigitalGauge");
    qmlRegisterType<LogWidgetController>("com.example3", 1, 0, "LogWidget");
    qmlRegisterType<DigitalInputIndicator>("com.example4", 1, 0, "DigitalInputIndicator");
    qmlRegisterType<InputButton>("com.example5", 1, 0, "InputButton");
    engine.rootContext()->setContextProperty("RPMProvider", &rpmProvider);
    SettingsHandler settingsHandler(&engine);
    engine.rootContext()->setContextProperty("settingsHandler", &settingsHandler);
    QObject::connect(&settingsHandler, &SettingsHandler::saveClicked,
                     &settingsHandler, &SettingsHandler::handleSaveClicked);
    QObject::connect(&settingsHandler, &SettingsHandler::startCanSimulatorClicked,
                     &settingsHandler, &SettingsHandler::handleStartCanSimulatorClicked);
    QObject::connect(&settingsHandler, &SettingsHandler::stopCanSimulatorClicked,
                        &settingsHandler, &SettingsHandler::handleStopCanSimulatorClicked);
    engine.load(url);
    QLineSeries *series = new QLineSeries();
    series->append(0, 0);
    series->append(1, 1);
    series->append(2, 4);
    series->append(3, 9);
    series->append(4, 16);

    int result = initializeGauges(&engine);
    //Set up the CAN input spoof helper
    canIOInputHandler.addSerialNumber(1234);
    //Start Threads
    thread ioThread(IOThread);
    thread canThread(canListenerThread, &settingsHandler);
    thread canProcessor(canProcessorThread);
    thread alarmThreadHandle(alarmThread);
    thread gpsThreadHandle(GPSThread);
    setThreadName(ioThread, "IOThread");
    setThreadName(canThread, "Can Listener Thread");
    setThreadName(canProcessor, "Can Processor Thread");
    setThreadName(alarmThreadHandle, "Alarm Thread");
    setThreadName(gpsThreadHandle, "GPS Thread");
    shell = new InteractiveShell();
    alarmEngine = new AlarmEngine();
    //Create time for main data loop
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&](){
        sem_wait(&gaugeDataSemaphore);
        acquireGaugeData(&currentGaugeData);
        currentGaugeData.coolantTemperature = 50;
        coolantGauge->setValue(currentGaugeData.coolantTemperature);
        oilPressureGauge->setValue(currentGaugeData.oilPressure);
        fuelLevelGauge->setValue(currentGaugeData.fuelLevel);
        digitalGauge1->setValue(oilPressure);
        digitalGauge2->setValue(oilTemperatureOhms);
        digitalGauge3->setValue(currentGaugeData.batteryVoltage);
        rpmProvider.setRpmFrame(currentGaugeData.RPM);
        speedgauge->setValue(currentGaugeData.vehicleSpeed);
        sem_post(&gaugeDataSemaphore);
    });
    //Start main data loop
    timer.start(25);
    return app.exec();
}

void IOThread(){
    printf("Starting IOThread\r\n");
    PacketHandler packetHandler;
    int timeoutCount = 0;
    int successCount = 0;
    uint8_t errOn = 0;
    while(1){
        if(errOn == 0){
            errOn = 1;
            errorLED = 1;
            warningLED = 1;
            okLED = 1;
            led0 = 1;
            led1 = 1;
            led2 = 1;
        }else{
            errOn = 0;
            errorLED = 0;
            warningLED = 0;
            okLED = 0;
            led0 = 0;
            led1 = 0;
            led2 = 0;
        }
        bool failure = false;
        //Write Outputs
        //Write Error LED
        uint8_t _err = errorLED.load();
        OperationResult result = packetHandler.writeServerMemory(0, &_err, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error writing to errorLED\r\n");
            timeoutCount++;
            failure = true;
        }
        uint8_t _warn = warningLED.load();
        result = packetHandler.writeServerMemory(1, &_warn, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error writing to warningLED\r\n");
            timeoutCount++;
            failure = true;
        }
        uint8_t _ok = okLED.load();
        result = packetHandler.writeServerMemory(2, &_ok, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error writing to okLED\r\n");
            timeoutCount++;
            failure = true;
        }
        uint8_t _led0 = led0.load();
        result = packetHandler.writeServerMemory(3, &_led0, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error writing to led0\r\n");
            timeoutCount++;
            failure = true;
        }
        uint8_t _led1 = led1.load();
        result = packetHandler.writeServerMemory(4, &_led1, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error writing to led1\r\n");
            timeoutCount++;
            failure = true;
        }
        uint8_t _led2 = led2.load();
        result = packetHandler.writeServerMemory(5, &_led2, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error writing to led2\r\n");
            timeoutCount++;
            failure = true;
        }

        //Read Inputs
        uint8_t _input0;
        result = packetHandler.readServerMemory(6, &_input0, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error reading input0\r\n");
            timeoutCount++;
            failure = true;
            continue;
        }
        input0 = _input0;
        uint8_t _input1;
        result = packetHandler.readServerMemory(7, &_input1, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error reading input1\r\n");
            timeoutCount++;
            failure = true;
            continue;
        }
        input1 = _input1;
        uint8_t _input2;
        result = packetHandler.readServerMemory(8, &_input2, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error reading input2\r\n");
            timeoutCount++;
            failure = true;
            continue;
        }
        input2 = _input2;
        uint8_t _input3;
        result = packetHandler.readServerMemory(9, &_input3, 1);
        if(result != OPERATION_SUCCESS){
            printf("Error reading input3\r\n");
            timeoutCount++;
            failure = true;
            continue;
        }
        input3 = _input3;
        //Print the input(s)
        //printf("Input0: %d, Input1: %d, Input2: %d, Input3: %d\r\n", _input0, _input1, _input2, _input3);
        if(!failure){
            successCount++;
        }
        //Compute failure percentage
        float failurePercentage = (float)timeoutCount / (float)(successCount + timeoutCount) * 100.0;
        //printf("Success: %d, Timeout: %d, RP2040 Failure Percentage: %f\r\n", successCount, timeoutCount, failurePercentage);

        /* Handle CAN input spoofing for Holley ECU */
        /*Generally, we will use a spoof serial of 1234 and map the 8 inputs to a struct defined in globals.h*/
        /*
         * Stock can module 1312 has ecu outputting to sourceSerial=10,SourceID=2,TargetSerial=8,TargetID=1,Command=0,DLC=0, data example is = 05500001
         *  (1719181393.831345) can0 0E002520#10 //Seems necessary to make ECU start sending output information
            (1719181393.831345) can0 0E002520#10
            (1719181393.831345) can0 0E002520#10
            (1719176035.993115) can0 0202100A#05200000
            (1719176036.005118) can0 0202100A#05200000
            (1719176036.005118) can0 0202100A#05200000
            (1719176036.005118) can0 0202100A#05200000
         */
        HolleyCANDecoder canDecoder;
        HolleyCANDecoder::can_message msg;
        HolleyCANDecoder::CanIdType canid = {0};
        HolleyCANDecoder::CanIdType fakeACKID = {0};
        char fakeACKValue[1] = {0x10};
        /* Other threads set the values of the inputs in the canIOInputHandler struct. We will spoof these values to the ECU
         * This program also supports the ability to act as an output module for the ECU.
         * The CAN IO thread listens for the output broadcasts and sets the values in the canIOInputHandler struct.
         */
        //The actual code that does the spoofing.
        for(int spoofChannel = 1; spoofChannel <= 8; spoofChannel++){
            float spoofValue = canIOInputHandler.getValue(1234, spoofChannel);
            char spoofValueFlipped[4] = {0};
            spoofValueFlipped[0] = ((char*)&spoofValue)[3];
            spoofValueFlipped[1] = ((char*)&spoofValue)[2];
            spoofValueFlipped[2] = ((char*)&spoofValue)[1];
            spoofValueFlipped[3] = ((char*)&spoofValue)[0];
            canid = canDecoder.generateCanID(1234, 4, 127+spoofChannel, 7, 1);
            fakeACKID = canDecoder.generateCanID(1234, 4, 0, 7, 0);
            msg = canDecoder.generateHEFIFrame(canid, spoofValueFlipped, 4);
            struct can_frame frame;
            frame.can_id = canDecoder.generateCanIDHEX(msg.id);
            frame.can_id = frame.can_id | CAN_EFF_FLAG;
            frame.can_dlc = msg.dlc;
            memcpy(&frame.data,&msg.data,msg.dlc);
            int spoofWriteResult = writeCANFrame(frame);
            usleep(1000*10);
            msg = canDecoder.generateHEFIFrame(fakeACKID, fakeACKValue, 1);
            frame.can_id = canDecoder.generateCanIDHEX(msg.id);
            frame.can_id = frame.can_id | CAN_EFF_FLAG;
            frame.can_dlc = msg.dlc;
            memcpy(&frame.data,&msg.data,msg.dlc);
            int ackWriteResult = writeCANFrame(frame);
            usleep(1000*10);
        }
        usleep(1000*50);
    }
}

uint32_t CONCAT31(uint32_t threeBytes, uint8_t oneByte) {
    // Ensure only the lower 3 bytes of threeBytes are used.
    threeBytes &= 0x00FFFFFF;
    // Shift the 3-byte value to the left by 8 bits to make room for the 1-byte value at the LSB.
    uint32_t result = threeBytes << 8;
    // Insert the 1-byte value into the LSB of the result.
    result |= oneByte;
    return result;
}
uint32_t CONCAT22(uint16_t high, uint16_t low) {
    return ((uint32_t)high << 16) | low;
}

void write11BitTo32Bit(uint16_t value, uint32_t *target, uint8_t position) {
    if (position > 20) {
        printf("Position out of range. Must be between 0 and 20.\n");
        return;
    }
    // Mask to keep only the lower 11 bits of the value
    uint16_t maskedValue = value & 0x07FF;
    // Clear the bits at the position in the target
    *target &= ~(((uint32_t)0x07FF) << position);
    // Set the bits according to the maskedValue
    *target |= ((uint32_t)maskedValue) << position;
}

// Function to read an 11-bit value from a 32-bit integer at a specified position
uint16_t read11BitFrom32Bit(uint32_t source, uint8_t position) {
    if (position > 20) {
        printf("Position out of range. Must be between 0 and 20.\n");
        return 0;
    }
    // Extract the 11-bit value
    return (source >> position) & 0x07FF;
}

void canProcessorThread(){
    //Pull CAN frames from the canFrameQueue and process them
    HolleyCANDecoder canDecoder;
    int canerrorframes = 0;
    while(1){
        //Wait for alarm rule engine to initialize
        if(alarmEngine == nullptr){
            usleep(1000*100);
            continue;
        }
        if(incomingCANFrames.size() > 0){
            if(incomingCANFrames.size() > 250){
                printf("size = %d\n", incomingCANFrames.size());
            }
            //Acquire lock on incomingCANFrames
            std::unique_lock<std::mutex> lock(incomingCANFramesMutex);
            //Get the first frame
            can_frame frame = incomingCANFrames.front();
            //Remove the frame from the queue
            incomingCANFrames.erase(incomingCANFrames.begin());

            HolleyCANDecoder::CanIdType decodedHolleyID = canDecoder.parseRawCanID(frame.can_id);
            HolleyCANDecoder::can_message message;
            message.id = decodedHolleyID;
            message.dlc = frame.can_dlc;
            memcpy(&message.data, &frame.data, frame.can_dlc);
            uint8_t data[8] = {0};
            memcpy(data, &frame.data, frame.can_dlc);
            if((frame.can_id & 0x20000000) != 0){
                canerrorframes = canerrorframes + 1;
                continue;
            }
            if((frame.can_id & 0x40000000) == 0){
                //Frame OK
                typedef struct {
                    uint32_t flags       : 3;
                    uint32_t SourceSerial: 11;
                    uint32_t SourceId    : 3;
                    uint32_t TargetSerial: 11;
                    uint32_t TargetId    : 3;
                    uint32_t Command     : 1;
                } CanIdTypeNew;
                CanIdTypeNew decodedHolleyID2 = {0};
                uint8_t *idPTR = (uint8_t*)&decodedHolleyID2;
                if((int)frame.can_id < 0) {
                    int iVar10 = frame.can_id << 3;
                    uint uVar11 = -(iVar10 >> 0x1f);
                    uint uVar9 = (frame.can_id << 4) >> 0x1d;
                    uint uVar13 = frame.can_id >> 0xb & 7;
                    uint uVar12 = frame.can_id >> 0xe;
                    int iVar1 = (frame.can_id & 0x7ff) << 3;
                    uint8_t array[3] = {0};
                    uint32_t *ptr = (uint32_t*)array;
                    *ptr = (uVar13 << 0xe);
                    memcpy(&decodedHolleyID2, ptr, 3);

                    uint8_t *ptr2 = (uint8_t*)&array[3];
                    *ptr2 = (uint8_t)((uVar11 & 1) << 7) | (uint8_t)(uVar9 << 4);
                    uint16_t uVar6 = *((uint16_t*)&array[2]);

                    uint8_t array2[3] = {0};
                    ptr2 = (uint8_t*)&array[1];
                    memcpy(array2, ptr, 3);
                    int16_t x = (int16_t)CONCAT31(*((uint32_t*)&array2), (uint8_t)iVar1);
                    uint32_t y = CONCAT22(uVar6 | (uint16_t)(uVar12 & 0x7ff) << 1, x);
                    ptr = (uint32_t*)&decodedHolleyID2;
                    *ptr = y;
                }
            }

            float val = -1.0f;
            char *ptr = (char*)&val;
            /*
 * Stock can module 1312 has ecu outputting to sourceSerial=10,SourceID=2,TargetSerial=8,TargetID=1,Command=0,DLC=0, data example is = 05500001
 *  (1719181393.831345) can0 0E002520#10 //Seems necessary to make ECU start sending output information
    (1719181393.831345) can0 0E002520#10
    (1719181393.831345) can0 0E002520#10
    (1719176035.993115) can0 0202100A#05200000
    (1719176036.005118) can0 0202100A#05200000
    (1719176036.005118) can0 0202100A#05200000
    (1719176036.005118) can0 0202100A#05200000
 */
            if(decodedHolleyID.sourceSerial == 10 && decodedHolleyID.sourceID == 2 && decodedHolleyID.targetSerial == 8){
                //Print the data for debugging right now.
                //Get the canbus extender's serial number
                volatile uint16_t extenderSerial = 0x0000;
                uint8_t *upperExtenderSerialByte = (uint8_t*)&extenderSerial+1;
                uint8_t *lowerExtenderSerialByte = (uint8_t*)&extenderSerial;
                *upperExtenderSerialByte = data[0];
                *lowerExtenderSerialByte = data[1];
                uint8_t  *extenderOutputNumber = (uint8_t*)&data[2];
                uint8_t  *pwmPercentValue = (uint8_t*)&data[3];//200 is 100%, 100 is 50%
                //Write this value to the canIOInputHandler struct
                //canIOInputHandler.setValue(extenderSerial, *extenderOutputNumber, *pwmPercentValue, CanIOInputHandler::valueType::OUTPUT);
                if(*extenderOutputNumber == 0 && extenderSerial == 1234){
                    //print data bytes as test
                    printf("Data: %02X %02X %02X %d %02X %02X\n", data[0], data[1], data[2], data[3], data[4], data[5]);
                }
            }
            //Oil temp from 1312 CAN I/O extender flags=0,sourceSerial=1312,sourceID=4,targetSerial=131,targetID=7,cmd=1,dlc=4
            if(decodedHolleyID.targetSerial == 131 && decodedHolleyID.sourceSerial == 1312){
                ptr[3] = data[0];
                ptr[2] = data[1];
                ptr[1] = data[2];
                ptr[0] = data[3];
                oilTemperatureOhms = val;
                continue;
            }
            if(decodedHolleyID.targetSerial == 130 && decodedHolleyID.sourceSerial == 1312){
                ptr[3] = data[0];
                ptr[2] = data[1];
                ptr[1] = data[2];
                ptr[0] = data[3];
                oilPressureOhms = val;
                continue;
            }
            canDecoder.generateCanIDHEX(1312,4,131,7,1);

            switch(frame.can_id){
                case BATTERY_VOLTAGE_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    batteryVoltage = val;
                    alarmEngine->updateSensorData("batteryVoltage", val);
                    //printf("Battery Voltage: %f\n", val);
                    break;
                case RPM_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    rpm = val;
                    //printf("RPM: %f\n", val);
                    break;
                case COOLANT_TEMP_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    coolantTemperature = val;
                    alarmEngine->updateSensorData("coolantTemp", val);
                    //printf("Coolant Temp: %f\n", val);
                    break;
                case THROTTLE_POSITION_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    throttlePosition = val;
                    alarmEngine->updateSensorData("throttlePosition", val);
                    //printf("Throttle Position: %f\n", val);
                    break;
                case MAP_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    //map = val;
                    //printf("MAP: %f\n", val);
                    break;
                case OIL_PRESSURE_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    oilPressure = val;
                    //printf("Oil Pressure: %f\n", val);
                    break;
                case KNOCK_LEVEL_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    knockLevel = val;
                    //printf("Knock Level: %f\n", val);
                    break;
                case INJECTOR_DUTY_CYCLE_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    injectorDutyCycle = val;
                    //printf("Injector Duty Cycle: %f\n", val);
                    break;
                case KNOCK_RETARD_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    knockRetard = val;
                    break;
                case IAC_CAN_ADDRESS:
                    ptr[3] = data[0];
                    ptr[2] = data[1];
                    ptr[1] = data[2];
                    ptr[0] = data[3];
                    iacPosition = val;
                    break;
            }

        }
        //Yield to other threads
        std::this_thread::yield();
    }
}
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// Custom print function
static int custom_print(lua_State *L) {
    //Get socket handle
    int clientSocketHandle = shell->getClientSocketFD();
    if(clientSocketHandle == -1){
        return -1;
    }
    int nargs = lua_gettop(L);
    for (int i = 1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            printf("%s", lua_tostring(L, i));
        }
        else {
            // Fall back to Lua's tostring method
            lua_getglobal(L, "tostring");
            lua_pushvalue(L, i);
            lua_call(L, 1, 1);
            const char *s = lua_tostring(L, -1);
            if(s){
                int bytes_written = write(clientSocketHandle, s, strlen(s));
                //Check for errors
                if(bytes_written < 0){
                    return luaL_error(L, "Failed to write to socket");
                }
            }
            lua_pop(L, 1);
        }
        if (i < nargs){// Tabulate separate args
            int bytes_written = write(clientSocketHandle, "\t", 1);
            //Check for errors
            if(bytes_written < 0){
                return luaL_error(L, "Failed to write to socket");
            }
        }
    }
    printf("\n");
    return 0;
}

// Custom read function
static int custom_read(lua_State *L) {
    //Get socker handle for shell
    int clientSocketHandle = shell->getClientSocketFD();
    if(clientSocketHandle == -1){
        return -1;
    }
    char buffer[256];
    if(read(clientSocketHandle, buffer, 256) > 0){
        lua_pushstring(L, buffer);
        return 1;
    }
    return luaL_error(L, "Failed to read input");
}

//This callback connects the alarm messages from Lua and prints them to the user, in this case being the custom log widget.
bool logWidgetFirstRun = true;
TimeoutManager logWidgetTimeout = {0};
void logWidgetCallback(bool errorState, const std::string& message) {
    if(logWidgetFirstRun){
        logWidgetFirstRun = false;
        set_timeout(&logWidgetTimeout, 1000);
    }
    Qt::GlobalColor color = errorState ? Qt::red : Qt::green;
    // Ensure the update is performed in the GUI thread by using invokeMethod
    QMetaObject::invokeMethod(logWidget, [message, color]() {
        //logWidget->clearLogEntries();
        logWidget->addLogEntry(message, color);
    }, Qt::QueuedConnection);

}

void alarmThread() {
    // Wait for alarm rule engine to initialize
    while (alarmEngine == nullptr) {
        usleep(1000 * 100);
    }
    printf("Alarm Thread started.\r\n");

    // Set the log handler
    alarmEngine->setLogHandler(logWidgetCallback);
    int count = 0;

    while (1) {
        // Ensure the update is performed in the GUI thread
        QMetaObject::invokeMethod(logWidget, [logWidget, count]() {
            logWidget->clearLogEntries();
            if (count == 5) {
                logWidget->update();
            }
        }, Qt::QueuedConnection);

        alarmEngine->evaluateRules(&currentGaugeData);

        if (count == 5) {
            count = 0;
        }

        usleep(1000 * 50);
        count++;
    }
}

void GPSThread(){
    rawVehicleSpeed = 33;//test value
    try {
        // Initialize the GPS with the default baud rate
        GPS gps("/dev/ttyUSB0", B9600);  // Replace with your serial port
        GPSManager gps_manager(gps);

        // Change the baud rate to 115200
        gps_manager.changeBaudRate(B115200);

        // Change the update rate to 10Hz
        gps_manager.changeUpdateRate(10);
        // Continuously update GPS Location
        while(1){
            //Get current location
            std::tuple<double,double,double> location = gps_manager.getLatLong();
            double time = std::get<0>(location);
            //std::cout << "Time: " << time << std::endl;
            rawVehicleSpeed = rawVehicleSpeed + 1;
            if(rawVehicleSpeed == 150){
                rawVehicleSpeed = 0;
            }
            usleep(1000*50);
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}