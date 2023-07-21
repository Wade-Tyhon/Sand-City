BUILD_DIR=build
include $(N64_INST)/include/n64.mk

ngin =	ngin64/tools/ngin64_VectorFunc.c \
		ngin64/tools/ngin64_SystemFunc.c \
		ngin64/tools/ngin64_TransformFunc.c \
		ngin64/NGin64_UserConfig.c \
		ngin64/renderer/ngin64_renderSettings.c \
		ngin64/renderer/ngin64_objRenderer.c \
		ngin64/input/ngin64_ControllerInput.c
		
src =	SandCity_Main.c \
		scenes/prefabs/castles/SC_Castles.c \
		scenes/prefabs/castles/SC_Castles_Controller.c \
		scenes/prefabs/objects/SC_Prefabs_Furniture.c \
		scenes/playfields/SC_Playfield_Small.c \
		scenes/playfields/SC_Playfield_Small_Controller.c \
		scenes/backgrounds/easybeach/SC_Backgrounds_SimpleBeach.c \
		scenes/SC_Scene_Beach.c\
		interface/models/SC_Playfield_UI.c\
		interface/SC_Interface.c\
		interface/SC_Playfield_Control.c\
		interface/SC_Menu_Control.c\


assets_png = $(wildcard assets/*.png)
wavesequence_png = $(wildcard assets/waves/*.png)
assets_ttf = $(wildcard assets/*.ttf)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64))) 

wave_assets_conv = $(addprefix filesystem/,$(notdir $(wavesequence_png:%.png=%.sprite)))

#assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)), $(notdir $(wavesequence_png:%.png=%.sprite)))


#----- Note ----- While adding in new assets, suppress unused variable warnings
CFLAGS := $(CFLAGS) -O2 -Wno-unused-variable
#CFLAGS := $(CFLAGS) -O2 

MKSPRITE_FLAGS ?=


all: SandCity.z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) --compress -o "$(dir $@)" "$<"

filesystem/%.sprite: assets/waves/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -f CI4 --compress -o "$(dir $@)" "$<"

filesystem/%.font64: assets/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) $(MKFONT_FLAGS) -o filesystem "$<"



$(BUILD_DIR)/SandCity.dfs: $(assets_conv)
$(BUILD_DIR)/SandCity.dfs: $(wave_assets_conv)
$(BUILD_DIR)/SandCity.elf: $(ngin:%.c=$(BUILD_DIR)/%.o)
$(BUILD_DIR)/SandCity.elf: $(src:%.c=$(BUILD_DIR)/%.o)


SandCity.z64: N64_ROM_TITLE="GL Demo"
SandCity.z64: $(BUILD_DIR)/SandCity.dfs

clean:
	rm -rf $(BUILD_DIR) SandCity.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
