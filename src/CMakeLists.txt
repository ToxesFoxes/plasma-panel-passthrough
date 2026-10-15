qt_add_qml_module(kz_inputpassthrough
    URI kz.toxesfoxes.inputpassthrough
    VERSION 1.0
    PLUGIN_TARGET kz_inputpassthrough
    NO_GENERATE_PLUGIN_SOURCE
    CLASS_NAME InputPassthroughPlugin
    SOURCES inputpassthrough.h inputpassthrough.cpp plugin.cpp
)
target_link_libraries(kz_inputpassthrough PRIVATE Qt6::Quick)

install(TARGETS kz_inputpassthrough
        DESTINATION ${KDE_INSTALL_QMLDIR}/kz/toxesfoxes/inputpassthrough)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qmldir
              ${CMAKE_CURRENT_BINARY_DIR}/kz_inputpassthrough.qmltypes
        DESTINATION ${KDE_INSTALL_QMLDIR}/kz/toxesfoxes/inputpassthrough)
