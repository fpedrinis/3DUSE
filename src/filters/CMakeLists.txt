add_subdirectory( Test )

add_library( filters SHARED
  ChangeDetection/ChangeDetection.cpp
  EnhanceCityGML/EnhanceMNT.cpp
  EnhanceCityGML/LinkCityGMLShape.cpp
  raytracing/Hit.cpp
  raytracing/Ray.cpp
  raytracing/RayTracing.cpp
  ShpExtrusion/ShpExtrusion.cpp
  Tiling/ASCCut.cpp
  Tiling/TilingCityGML.cpp
)

target_include_directories( filters PUBLIC
  ${VCITYCORE_INCLUDE_DIR}
  ${CITYGMLUTILS_INCLUDE_DIR}
)

target_link_libraries(filters
  ${VCITYCORE_LIBRARY}
  ${CITYGMLUTILS_LIBRARIES}
)

if (WITH_QT5)
  # FIXME: refer to src/CMakeLists.txt to remove usage of QT5_USE_MODULES
	QT5_USE_MODULES(filters Core)
endif(WITH_QT5)

GENERATE_EXPORT_HEADER( filters )