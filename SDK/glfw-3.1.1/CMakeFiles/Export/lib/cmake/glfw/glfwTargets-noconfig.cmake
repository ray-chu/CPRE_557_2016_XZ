#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glfw" for configuration ""
set_property(TARGET glfw APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(glfw PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "/System/Library/Frameworks/Cocoa.framework;/System/Library/Frameworks/OpenGL.framework;/System/Library/Frameworks/IOKit.framework;/System/Library/Frameworks/CoreFoundation.framework;/System/Library/Frameworks/CoreVideo.framework"
  IMPORTED_LOCATION_NOCONFIG "/Users/Raye/Project/ME557/HCI-557-CG/SDK/lib/libglfw.dylib"
  IMPORTED_SONAME_NOCONFIG "/usr/local/lib/libglfw.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS glfw )
list(APPEND _IMPORT_CHECK_FILES_FOR_glfw "/Users/Raye/Project/ME557/HCI-557-CG/SDK/lib/libglfw.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
