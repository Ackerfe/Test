# Install script for directory: C:/Test/Dependencies/cegui-0.8.7/cegui/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/cegui")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Test/Dependencies/cegui-0.8.7/build/lib/CEGUIBase-0_d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Test/Dependencies/cegui-0.8.7/build/lib/CEGUIBase-0.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Test/Dependencies/cegui-0.8.7/build/lib/CEGUIBase-0.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Test/Dependencies/cegui-0.8.7/build/lib/CEGUIBase-0.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Test/Dependencies/cegui-0.8.7/build/bin/CEGUIBase-0_d.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Test/Dependencies/cegui-0.8.7/build/bin/CEGUIBase-0.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Test/Dependencies/cegui-0.8.7/build/bin/CEGUIBase-0.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Test/Dependencies/cegui-0.8.7/build/bin/CEGUIBase-0.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI" TYPE FILE FILES
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Affector.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Animation.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/AnimationInstance.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/AnimationManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Animation_xmlHandler.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Base.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/BasicImage.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/BasicRenderedStringParser.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/BidiVisualMapping.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/BoundSlot.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/CEGUI.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/CentredRenderedString.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ChainedXMLHandler.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Clipboard.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Colour.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ColourRect.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/CompositeResourceProvider.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Config_xmlHandler.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/CoordConverter.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/DataContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/DefaultLogger.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/DefaultRenderedStringParser.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/DefaultResourceProvider.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/DynamicModule.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Element.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Event.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/EventArgs.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/EventSet.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Exceptions.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FactoryModule.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FactoryRegisterer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Font.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FontGlyph.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FontManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Font_xmlHandler.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FormattedRenderedString.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ForwardRefs.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FreeFunctionSlot.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FreeTypeFont.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FribidiVisualMapping.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FunctorCopySlot.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FunctorPointerSlot.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FunctorReferenceBinder.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/FunctorReferenceSlot.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/GUIContext.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/GUILayout_xmlHandler.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/GeometryBuffer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/GlobalEventSet.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/IconvStringTranscoder.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Image.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ImageCodec.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ImageFactory.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ImageManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/InjectedInputReceiver.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/InputEvent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Interpolator.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/IteratorBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/JustifiedRenderedString.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/KeyFrame.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/LeftAlignedRenderedString.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/LinkedEvent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Logger.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MemberFunctionSlot.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MemoryAllocatedObject.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MemoryAllocation.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MemoryOgreAllocator.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MemorySTLWrapper.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MemoryStdAllocator.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MinibidiVisualMapping.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MinizipResourceProvider.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/MouseCursor.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/NamedElement.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/NamedXMLResourceManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/PCRERegexMatcher.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/PixmapFont.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Property.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/PropertyHelper.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/PropertySet.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Quaternion.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Rect.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RefCounted.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RegexMatcher.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderEffect.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderEffectFactory.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderEffectManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderQueue.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderTarget.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderedString.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderedStringComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderedStringImageComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderedStringParser.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderedStringTextComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderedStringWidgetComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderedStringWordWrapper.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Renderer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderingContext.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderingSurface.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RenderingWindow.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ResourceProvider.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/RightAlignedRenderedString.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Scheme.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/SchemeManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Scheme_xmlHandler.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/ScriptModule.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/SimpleTimer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Singleton.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Size.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/SlotFunctorBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/String.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/StringTranscoder.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/SubscriberSlot.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/System.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/SystemKeys.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TextUtils.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Texture.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TextureTarget.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplInterpolators.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplProperty.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplWRFactoryRegisterer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplWindowFactory.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplWindowFactoryRegisterer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplWindowProperty.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplWindowRendererFactory.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TplWindowRendererProperty.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/TypedProperty.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/UDim.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Vector.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Vertex.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Win32StringTranscoder.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/Window.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/WindowFactory.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/WindowFactoryManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/WindowManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/WindowRenderer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/WindowRendererManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/XMLAttributes.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/XMLHandler.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/XMLParser.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/XMLSerializer.h"
    "C:/Test/Dependencies/cegui-0.8.7/build/cegui/src/../include/CEGUI/Config.h"
    "C:/Test/Dependencies/cegui-0.8.7/build/cegui/src/../include/CEGUI/ModuleConfig.h"
    "C:/Test/Dependencies/cegui-0.8.7/build/cegui/src/../include/CEGUI/Version.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/widgets" TYPE FILE FILES
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/All.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ButtonBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ClippedContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ComboDropList.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Combobox.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/DefaultWindow.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/DragContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Editbox.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/FrameWindow.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/GridLayoutContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/GroupBox.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/HorizontalLayoutContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ItemEntry.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ItemListBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ItemListbox.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/LayoutCell.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/LayoutContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ListHeader.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ListHeaderSegment.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Listbox.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ListboxItem.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ListboxTextItem.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/MenuBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/MenuItem.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Menubar.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/MultiColumnList.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/MultiLineEditbox.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/PopupMenu.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ProgressBar.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/PushButton.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/RadioButton.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ScrollablePane.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Scrollbar.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ScrolledContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ScrolledItemListBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/SequentialLayoutContainer.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Slider.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Spinner.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/TabButton.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/TabControl.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Thumb.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Titlebar.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/ToggleButton.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Tooltip.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/Tree.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/TreeItem.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/widgets/VerticalLayoutContainer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/falagard" TYPE FILE FILES
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/ComponentBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/Dimensions.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/Enums.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/EventAction.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/EventLinkDefinition.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/FalagardPropertyBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/FormattingSetting.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/FrameComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/ImageryComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/ImagerySection.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/LayerSpecification.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/NamedArea.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/NamedDefinitionCollator.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/PropertyDefinition.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/PropertyDefinitionBase.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/PropertyInitialiser.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/PropertyLinkDefinition.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/SectionSpecification.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/StateImagery.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/TextComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/WidgetComponent.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/WidgetLookFeel.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/WidgetLookManager.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/XMLEnumHelper.h"
    "C:/Test/Dependencies/cegui-0.8.7/cegui/src/../include/CEGUI/falagard/XMLHandler.h"
    )
endif()

