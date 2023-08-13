BUILD_DIR=build
include $(N64_INST)/include/n64.mk

ngin =	ngin64/tools/ngin64_VectorFunc.c \
		ngin64/tools/ngin64_SystemFunc.c \
		ngin64/tools/ngin64_TransformFunc.c \
		ngin64/gui/ngin64_GUI.c \
		ngin64/NGin64_UserConfig.c \
		ngin64/renderer/ngin64_renderSettings.c \
		ngin64/renderer/ngin64_objRenderer.c \
		ngin64/input/ngin64_ControllerInput.c\
		ngin64/events/ngin64_Events.c\
		ngin64/events/ngin64_EventManager.c\
		ngin64/audio/ngin64_XMAudio.c\
		
src =	SandCity_Main.c \
		scenes/prefabs/castles/SC_Castles.c \
		scenes/prefabs/castles/SC_Castles_Controller.c \
		scenes/prefabs/creatures/SC_Crabs.c \
		scenes/prefabs/objects/SC_Prefabs_Furniture.c \
		scenes/playfields/SC_Playfield_Small.c \
		scenes/playfields/SC_Playfield_Small_Controller.c \
		scenes/backgrounds/easybeach/SC_Backgrounds_SimpleBeach.c \
		scenes/SC_Scene_Beach.c\
		interface/models/SC_Playfield_UI.c\
		interface/SC_Interface.c\
		interface/SC_Playfield_GUI.c\
		interface/SC_Playfield_Events.c\
		interface/SC_Playfield_Manager.c\
		interface/SC_Menu_Manager.c\


assets_png = $(wildcard assets/*.png)
uiassets_png = $(wildcard assets/ui/*.png)
wavesequence_png = $(wildcard assets/waves/*.png)
assets_ttf = $(wildcard assets/*.ttf)
assets_xm = $(wildcard assets/audio/*.xm)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64)))
			  

ui_assets_conv = $(addprefix filesystem/ui/,$(notdir $(uiassets_png:%.png=%.sprite)))
wave_assets_conv = $(addprefix filesystem/,$(notdir $(wavesequence_png:%.png=%.sprite)))
audio_assets_conv = $(addprefix filesystem/,$(notdir $(assets_xm:%.xm=%.xm64)))

#assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)), $(notdir $(wavesequence_png:%.png=%.sprite)))


#----- Note ----- While adding in new assets, suppress unused variable warnings
CFLAGS := $(CFLAGS) -O2 -Wno-unused-variable
#CFLAGS := $(CFLAGS) -O2 

MKSPRITE_FLAGS ?=

AUDIOCONV_FLAGS ?=

all: SandCity.z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) --compress -o "$(dir $@)" "$<"

filesystem/%.sprite: assets/ui/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -f CI4 --compress -o "$(dir $@)" "$<"


filesystem/%.xm64: assets/audio/%.xm
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o "$(dir $@)" "$<"





filesystem/%.sprite: assets/waves/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -f CI4 --compress -o "$(dir $@)" "$<"

filesystem/%.font64: assets/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) $(MKFONT_FLAGS) -o filesystem "$<"





$(BUILD_DIR)/SandCity.dfs: $(assets_conv)
$(BUILD_DIR)/SandCity.dfs: $(ui_assets_conv)
$(BUILD_DIR)/SandCity.dfs: $(wave_assets_conv)
$(BUILD_DIR)/SandCity.dfs: $(audio_assets_conv)
$(BUILD_DIR)/SandCity.elf: $(ngin:%.c=$(BUILD_DIR)/%.o)
$(BUILD_DIR)/SandCity.elf: $(src:%.c=$(BUILD_DIR)/%.o)


SandCity.z64: N64_ROM_TITLE="GL Demo"
SandCity.z64: $(BUILD_DIR)/SandCity.dfs

clean:
	rm -rf $(BUILD_DIR) SandCity.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
