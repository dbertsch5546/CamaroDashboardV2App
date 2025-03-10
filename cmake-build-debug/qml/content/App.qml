// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import CamaroDashboardV2

Window {
    width: mainScreen.width
    height: mainScreen.height
    //visibility: "FullScreen"  // This will start the window in full screen
    visible: true
    title: "CamaroDashboardV2"

    Screen01 {
        id: mainScreen
    }

}

