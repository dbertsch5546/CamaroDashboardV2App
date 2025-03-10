file(REMOVE_RECURSE
  "../../qml/CamaroDashboardV2/Constants.qml"
  "../../qml/CamaroDashboardV2/DirectoryFontLoader.qml"
  "../../qml/CamaroDashboardV2/EventListModel.qml"
  "../../qml/CamaroDashboardV2/EventListSimulator.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/CamaroDashboardV2_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
