#Todo

##Application
- Make framebuffer resize callbacks use `glm::ivec2`

##ECS
- Less tedious `getComponent()` method

##Framebuffers
- Fix occasional flickering on framebuffer resize
- GBuffer

##Player
good

##Renderer
- Load normal matrix uniform correctly adjusted for scaled objects [link](https://learnopengl.com/#!Lighting/Basic-Lighting)

#Completed

##Framebuffers
- Framebuffer manager
	- Clear automatically on each frame
	- ImGUI browser/viewer
	- Resize with viewport

##Player
- Limit vertical viewing angles
- Fix mouse not hiding (issue with ImGUI)
- Fix movement when looking directly up or down
