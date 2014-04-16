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
    SceneGraph/Node.cpp
    SceneGraph/Renderer.cpp
	SceneGraph/SceneGraph.cpp
    SceneGraph/ShaderNode.cpp
	SceneGraph/ShaderProgramGL.cpp
    SceneGraph/VertexNode.cpp
)

set(SCENEGRAPH_HEADERS
    SceneGraph/CameraNode.h
    SceneGraph/DrawMethodNode.h
    SceneGraph/GeometryNode.h
    SceneGraph/GroupNode.h
    SceneGraph/IndexNode.h
    SceneGraph/Node.h
    SceneGraph/Renderer.h
	SceneGraph/SceneGraph.h
    SceneGraph/ShaderNode.h
	SceneGraph/ShaderProgramGL.h
    SceneGraph/VertexNode.h
)

source_group(SceneGraph FILES ${SCENEGRAPH_SOURCES} ${SCENEGRAPH_HEADERS})

qt4_wrap_cpp(MOC_SRCS View3d.h)

set(SOURCES
    ${SCENEGRAPH_SOURCES} 
	${SCENEGRAPH_HEADERS}
    ${MOC_SRCS}
    GenericDataArray.h
    main.cpp
    Mesh.cpp
    Mesh.h
    View3d.cpp
    View3d.h
	ViewNavigator.cpp
	ViewNavigator.h
)

add_executable(SMeshViewer ${SOURCES})
target_link_libraries(SMeshViewer ${QT_LIBRARIES} ${GLEW_LIBRARY})