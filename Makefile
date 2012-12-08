TARGETS=	bin/Debug/Slysics

PROJECT=	../..

CXXFLAGS=	-g -O2 -DDEBUGINFO

LDFLAGS=	-lBox2D -lSDL -lSDLmain -lSDL_image -lSDL_gfx -lSDL_ttf -lpng \

SOURCES=	src/Core/GUI/Widgets/Keyboard.cpp \
		src/Core/GUI/Widgets/RadioButton.cpp \
		src/Core/Physics/PhysicsCore.cpp \
		src/Core/Rendering/ImageObject.cpp \
		src/Core/Rendering/RenderingCore.cpp \
		src/Core/Rendering/TTFFont.cpp \
		src/Core/Rendering/TextLabel.cpp \
		src/Core/Rendering/UpdateRectManager.cpp \
		src/Core/System/ConfigurationCore.cpp \
		src/Core/System/TimerCore.cpp \
		src/Core/SlysicsCore.cpp \
		src/Core/SlysicsCoreRender.cpp \
		src/Game/ConfigurationMenu.cpp \
		src/Game/FlagManager.cpp \
		src/Game/Portal.cpp \
		src/Game/GameCanvas.cpp \
		src/Game/Line.cpp \
		src/Game/LoadMenu.cpp \
		src/Game/Sled.cpp \
		src/Game/Sledder.cpp \
		src/Slysics.cpp 

ifneq ($(INCLUDE_DEPENDENCIES),yes)

Debug:
	mkdir -p ./bin/Debug
	@make --no-print-directory INCLUDE_DEPENDENCIES=yes $(TARGETS) \

.PHONY:	clean
clean:
	rm -rf obj/Debug; rm -rf bin/Debug

else

-include $(addprefix obj/Debug/,$(SOURCES:.cpp=.d))

endif

FIXED_OBJECTS= $(addprefix obj/Debug/,$(SOURCES:.cpp=.o))

obj/Debug/%.o:		%.cpp
	mkdir -p $(dir $@)
	c++ $(CXXFLAGS) -c -o $@ $<

bin/Debug/Slysics:	$(FIXED_OBJECTS) /usr/lib/libBox2D.a
	g++ -rdynamic -o $@ $^ $(LDFLAGS)

obj/Debug/%.d:		%.cpp
	@mkdir -p $(dir $@)
	c++ -M -MT $(@:.d=.o) $(CXXFLAGS) -o $@ $<

