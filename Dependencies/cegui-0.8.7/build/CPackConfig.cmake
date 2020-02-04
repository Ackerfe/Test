# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "C:/Test/Dependencies/cegui-0.8.7;C:/Test/Dependencies/cegui-0.8.7/build")
set(CPACK_CMAKE_GENERATOR "Visual Studio 15 2017")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.16/Templates/CPack.GenericDescription.txt")
set(CPACK_GENERATOR "NSIS")
set(CPACK_INSTALL_CMAKE_PROJECTS "C:/Test/Dependencies/cegui-0.8.7/build;cegui;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/cegui")
set(CPACK_MODULE_PATH "C:/Test/Dependencies/cegui-0.8.7/cmake")
set(CPACK_NSIS_DISPLAY_NAME "cegui 0.8.7")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "cegui 0.8.7")
set(CPACK_OUTPUT_CONFIG_FILE "C:/Test/Dependencies/cegui-0.8.7/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Test/Dependencies/cegui-0.8.7/README.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Crazy Eddie's Gui System")
set(CPACK_PACKAGE_FILE_NAME "cegui-0.8.7-win32")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "cegui 0.8.7")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "cegui 0.8.7")
set(CPACK_PACKAGE_NAME "cegui")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "CEGUI team")
set(CPACK_PACKAGE_VERSION "0.8.7")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "8")
set(CPACK_PACKAGE_VERSION_PATCH "7")
set(CPACK_RESOURCE_FILE_LICENSE "C:/Test/Dependencies/cegui-0.8.7/COPYING")
set(CPACK_RESOURCE_FILE_README "C:/Program Files/CMake/share/cmake-3.16/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files/CMake/share/cmake-3.16/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "TBZ2;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "\\.hg.*;cppcheck-output;perform-cppcheck;build/;~$;\\.orig$;Thumbs.db;\\.directory;\\.kdev4;\\.settings;\\.project;\\.cproject;\\.pydevproject;\\.ropeproject")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Test/Dependencies/cegui-0.8.7/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "cegui-0.8.7")
set(CPACK_SOURCE_RPM "")
set(CPACK_SOURCE_TBZ2 "")
set(CPACK_SOURCE_TGZ "")
set(CPACK_SOURCE_TXZ "")
set(CPACK_SOURCE_TZ "")
set(CPACK_SOURCE_ZIP "")
set(CPACK_SYSTEM_NAME "win32")
set(CPACK_TOPLEVEL_TAG "win32")
set(CPACK_WIX_SIZEOF_VOID_P "4")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Test/Dependencies/cegui-0.8.7/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
