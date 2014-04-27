include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/SceneGraph
)

set(SCENEGRAPH_SOURCES
    SceneGraph/CameraNode.cpp 
    SceneGraph/DrawMethodNode.cpp
    SceneGraph/GeometryNode.cpp
    SceneGraph/GroupNode.cpp
    SceneGraph/IndexNode.cpp
	SceneGraph/LightDirectionalNode.cpp
    SceneGraph/Node.cpp
	SceneGraph/NormalNode.cpp
    SceneGraph/Renderer.cpp
	SceneGraph/SceneGraph.cpp
    SceneGraph/ShaderNode.cpp
	SceneGraph/ShaderProgramGL.cpp
    SceneGraph/TransformNode.h
    SceneGraph/VertexNode.cpp
)

set(SCENEGRAPH_HEADERS
    SceneGraph/CameraNode.h
    SceneGraph/DrawMethodNode.h
    SceneGraph/GeometryNode.h
    SceneGraph/GroupNode.h
    SceneGraph/IndexNode.h
	SceneGraph/LightDirectionalNode.h
    SceneGraph/Node.h
	SceneGraph/NormalNode.h
    SceneGraph/Renderer.h
	SceneGraph/SceneGraph.h
    SceneGraph/ShaderNode.h
	SceneGraph/ShaderProgramGL.h
    SceneGraph/TransformNode.h
    SceneGraph/VertexNode.h
)

source_group(SceneGraph FILES ${SCENEGRAPH_SOURCES} ${SCENEGRAPH_HEADERS})

qt4_wrap_cpp(MOC_SRCS View3d.h MainWindow.h)
qt4_add_resources(RCC_SRCS icons.qrc)

set(SOURCES
    ${SCENEGRAPH_SOURCES} 
	${SCENEGRAPH_HEADERS}
    ${MOC_SRCS}
    ${RCC_SRCS}
    GenericDataArray.h
    main.cpp
	MainWindow.cpp
	MainWindow.h
    Mesh.cpp
    Mesh.h
    Transform.cpp
    Transform.h
    View3d.cpp
    View3d.h
	ViewNavigator.cpp
	ViewNavigator.h
)

add_executable(SMeshViewer ${SOURCES})
target_link_libraries(SMeshViewer ${QT_LIBRARIES} ${GLEW_LIBRARY})