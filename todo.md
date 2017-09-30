#Todo

##Application
- Make framebuffer resize callbacks use `glm::ivec2`

##ECS
good

##Framebuffers
- Fix occasional flickering on framebuffer resize

##Player
good

##Renderer
good

#Completed

##ECS
- Less tedious `getComponent()` method

##Framebuffers
- Framebuffer manager
	- Clear automatically on each frame
	- ImGUI browser/viewer
	- Resize with viewport
- GBuffer

##Player
- Limit vertical viewing angles
- Fix mouse not hiding (issue with ImGUI)
- Fix movement when looking directly up or down

##Renderer
- Load normal matrix uniform correctly adjusted for scaled objects [link](https://learnopengl.com/#!Lighting/Basic-Lighting)
