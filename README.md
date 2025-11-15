# libanm2

A simple library that handles the serialization of .anm2 files (a format from The Binding of Isaac: Rebirth) to use in one's own program. 

Depends on tinyxml2; make sure your project includes that in a way these files can see.

To have the .anm2 file manage resources (i.e., textures and sounds), provide the equivalent callback (TextureCallback/SoundCallback) that will load a std::shared_ptr to your resource.

Define ANM2_LITE to remove some unneeded members in a typical game context.