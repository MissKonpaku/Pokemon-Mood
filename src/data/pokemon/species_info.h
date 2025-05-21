#include "constants/abilities.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
    .affineAnims = gDummySpriteAffineAnimTable,                                                                                         \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
            .affineAnims = gDummySpriteAffineAnimTable,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    //P_FAMILY_LILICHEN
    //BackPickYOffset starts at -8 
    
    [SPECIES_LILICHEN] =
    {
        .baseHP        = 50,
        .baseAttack    = 50,
        .baseDefense   = 71,
        .baseSpAttack  = 50,
        .baseSpDefense = 60,
        .baseSpeed     = 39,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 90,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_GRASSY_SURGE},
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Lilichen"),
        .categoryName = _("Lichen"),
        .height = 4,
        .weight = 10,
        .description = COMPOUND_STRING(
            "A sa naissance, il reçoit\n"
            "son tronc de la part de\n"
            "son Roi. Les deux organismes\n"
            "croissent en symbiose."),
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_NOBLICHEN}),
        //-------------------------------------------------------------//
        .cryId = CRY_NONE,
        //.natDexNum = NATIONAL_DEX_LILICHEN,
        .pokemonScale = 356,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Lilichen,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 9,
        .backPic = gMonBackPic_Lilichen,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
    
        .palette = gMonPalette_Lilichen,
        .shinyPalette = gMonShinyPalette_Lilichen,
        .iconSprite = gMonIcon_Lilichen,
        .iconPalIndex = 1,

        .levelUpLearnset = sLilichenLevelUpLearnset,
        //-------------------------------------------------------------//
    },
    
    [SPECIES_NOBLICHEN] =
    {
        .baseHP        = 65,
        .baseAttack    = 69,
        .baseDefense   = 91,
        .baseSpAttack  = 62,
        .baseSpDefense = 78,
        .baseSpeed     = 40,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 142,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_GRASSY_SURGE},
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Noblichen"),
        .categoryName = _("Lichen"),
        .height = 10,
        .weight = 200,
        .description = COMPOUND_STRING(
            "Lorsque qu'il évolue, il quitte\n"
            "directement son groupe pour\n"
            "créer sa propre colonie.\n"
            "Ce Pokémon a mauvais caractère."),
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_MONARCHEN}),
        //-------------------------------------------------------------//
        .cryId = CRY_NONE,
        //.natDexNum = NATIONAL_DEX_NOBLICHEN,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Noblichen,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 5,
         
        .backPic = gMonBackPic_Noblichen,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Noblichen,
        .shinyPalette = gMonShinyPalette_Noblichen,
        .iconSprite = gMonIcon_Noblichen,
        .iconPalIndex = 4,

        .levelUpLearnset = sNoblichenLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        //-------------------------------------------------------------//
        
    },

    [SPECIES_MONARCHEN] =
    {   

        .baseHP        = 85,
        .baseAttack    = 86,
        .baseDefense   = 122,
        .baseSpAttack  = 87,
        .baseSpDefense = 100,
        .baseSpeed     = 45,
        .types = MON_TYPES(TYPE_GRASS, TYPE_POISON),
        .catchRate = 45,
        .expYield = 263,
        .evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_GRASSY_SURGE},
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Monarchen"),
        .categoryName = _("Monarque"),
        .height = 20,
        .weight = 4000,
        .description = COMPOUND_STRING(
            "Monarchen dirige sa colonie\n"
            "avec fermeté. Malgré sa froideur,\n"
            "il préfère sa colonie à sa propre\n"
            "vie."),
        //-------------------------------------------------------------//
        .cryId = CRY_NONE,
        //.natDexNum = NATIONAL_DEX_MONARCHEN,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        
        .frontPic = gMonFrontPic_Monarchen,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 5,
         
        .backPic = gMonBackPic_Monarchen,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Monarchen,
        .shinyPalette = gMonShinyPalette_Monarchen,
        .iconSprite = gMonIcon_Monarchen,
        .iconPalIndex = 4,

        .levelUpLearnset = sMonarchenLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_LILICHEN

    //P_FAMILY_BEEMBER

    [SPECIES_BEEMBER] =
    {
        .baseHP        = 44,
        .baseAttack    = 45,
        .baseDefense   = 51,
        .baseSpAttack  = 72,
        .baseSpDefense = 48,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_FIRE, TYPE_BUG),
        .catchRate = 45,
        .expYield = 87,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_TINTED_LENS },
        
        .speciesName = _("Beember"),
        .categoryName = _("Larve Canon"),
        .height = 3,
        .weight = 30,
        //data
        .evYield_SpAttack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //Souvent la cible de pokémon oiseaux, il se défend en projetant des flammes sur ses adversaires pour pouvoir s'enfuir.
            "Souvent la cible des pokémon oiseaux,\n"
            "il se défend en projetant des flammes\n"
            "sur ses adversaires pour pouvoir fuir."),
        //.natDexNum = NATIONAL_DEX_BEEMBER,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 255,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Beember,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
         
        .backPic = gMonBackPic_Beember,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Beember,
        .shinyPalette = gMonShinyPalette_Beember,
        .iconSprite = gMonIcon_Beember,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBeemberLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_DETOPTERE}),
    },

    [SPECIES_DETOPTERE] =
    {
        .baseHP        = 65,
        .baseAttack    = 55,
        .baseDefense   = 65,
        .baseSpAttack  = 80,
        .baseSpDefense = 50,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_FIRE, TYPE_BUG),
        .catchRate = 45,
        .expYield = 140,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_TINTED_LENS },
        
        .speciesName = _("Detoptère"),
        .categoryName = _("Cannonier"),
        .height = 11,
        .weight = 190,
        //data
        //.natDexNum = NATIONAL_DEX_DETOPTERE,
        .evYield_SpAttack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //entrain d'orgamiser des compétitions d'explosion pour savoir qui est le Detoptere le plus fort du groupe.
            "Des chercheurs ont déjà surpris ces\n"
            "pokémon entrain d'organiser des\n"
            "compétitions d'explosion pour savoir\n"
            "qui est le Detoptere le plus fort."),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 255,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Detoptere,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Detoptere,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Detoptere,
        .shinyPalette = gMonShinyPalette_Detoptere,
        .iconSprite = gMonIcon_Detoptere,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sDetoptereLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_ACIDOPTE}),
    },

    [SPECIES_ACIDOPTE] =
    {
        .baseHP        = 74,
        .baseAttack    = 60,
        .baseDefense   = 91,
        .baseSpAttack  = 117,
        .baseSpDefense = 68,
        .baseSpeed     = 115,
        .types = MON_TYPES(TYPE_FIRE, TYPE_STEEL),
        .catchRate = 45,
        .expYield = 230,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_TINTED_LENS },
        
        .speciesName = _("Acidopte"),
        .categoryName = _("Bombardier"),
        .height = 16,
        .weight = 2400,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //Malgré sa très lourde carapace, Acidopte arrive à se déplacer avec agilité durant ses combats. La puissance de frappe de son canon est phénoménale.
            "Malgré sa très lourde carapace, Acidopte\n"
            "arrive à se déplacer avec agilité durant\n"
            "ses combats. La puissance de frappe de\n"
            "son canon est phénoménale."),
        //.natDexNum = NATIONAL_DEX_ACIDOPTE,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 255,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Acidopt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Acidopt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Acidopt,
        .shinyPalette = gMonShinyPalette_Acidopt,
        .iconSprite = gMonIcon_Acidopt,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sAcidoptLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_BEEMBER

    //P_FAMILY_WOOPEEL

    [SPECIES_WOOPEEL] =
    {
        .baseHP        = 43,
        .baseAttack    = 54,
        .baseDefense   = 48,
        .baseSpAttack  = 52,
        .baseSpDefense = 53,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_WATER),  
        .catchRate = 45,
        .expYield = 67,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_SHEER_FORCE },
        
        .speciesName = _("Woopeel"),
        .categoryName = _("MiniAnguille"),
        .height = 5,
        .weight = 30,
        //data
        .evYield_Attack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //Mignon mais dangereux, des dresseurs imprudents ont perdu la vie en se baignant trop près d’eux, victimes de décharges électriques.
            "Mignon mais dangereux, des dresseurs\n"
            "imprudents ont perdu la vie en se\n"
            "baignant trop près d'eux, victimes\n"
            "de décharges électriques."),
        //.natDexNum = NATIONAL_DEX_WOOPEEL,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 255,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Woopeel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .enemyMonElevation = 14,
         
        .backPic = gMonBackPic_Woopeel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Woopeel,
        .shinyPalette = gMonShinyPalette_Woopeel,
        .iconSprite = gMonIcon_Woopeel,
        .iconPalIndex = 2,
        //learnsets
        .levelUpLearnset = sWoopeelLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_CRUEEL}),
    },

    [SPECIES_CRUEEL] =
    {
        .baseHP        = 49,
        .baseAttack    = 90,
        .baseDefense   = 65,
        .baseSpAttack  = 62,
        .baseSpDefense = 65,
        .baseSpeed     = 74,
        .types = MON_TYPES(TYPE_WATER, TYPE_ELECTRIC),
        .catchRate = 45,
        .expYield = 150,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_SHEER_FORCE },
        
        .speciesName = _("Crueel"),
        .categoryName = _("Anguille"),
        .height = 10,
        .weight = 250,
        //data
        .evYield_Attack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //Probablement le meilleur ami des pêcheurs. En plongeant sa queue dans l’eau il déverse de l’électricité qui fait remonter des poissons grillés à la surface.
            "Probablement le meilleur ami des pêcheurs.\n"
            "En plongeant sa queue dans l’eau il déverse\n"
            "de l’électricité qui fait remonter des\n"
            "poissons grillés à la surface."),
        //.natDexNum = NATIONAL_DEX_CRUEEL,        
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 255,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Crueel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 12,
        .enemyMonElevation = 14,
         
        .backPic = gMonBackPic_Crueel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Crueel,
        .shinyPalette = gMonShinyPalette_Crueel,
        .iconSprite = gMonIcon_Crueel,
        .iconPalIndex = 2,
        //learnsets
        .levelUpLearnset = sCrueelLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_HORRIFEEL}),
    },

    [SPECIES_HORRIFEEL] =
    {
        .baseHP        = 83,
        .baseAttack    = 114,
        .baseDefense   = 75,
        .baseSpAttack  = 84,
        .baseSpDefense = 75,
        .baseSpeed     = 94,
        .types = MON_TYPES(TYPE_WATER, TYPE_ELECTRIC),
        .catchRate = 45,
        .expYield = 210,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_SHEER_FORCE },
        
        .speciesName = _("Horrifeel"),
        .categoryName = _("Prédateur"),
        .height = 20,
        .weight = 1300,
        //data
        .evYield_Attack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //Horrifeel est un superprédateurs. Ce chasseur patient ne laisse aucune chance à ses victimes. Sa deuxième bouche possède son propre estomac.
            "Horrifeel est un superprédateur.\n"
            "Ce chasseur patient ne laisse aucune\n"
            "chance à ses victimes. Sa deuxième\n"
            "bouche possède son propre estomac."),
        //.natDexNum = NATIONAL_DEX_HORRIFEEL,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 255,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Horrifeel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Horrifeel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Horrifeel,
        .shinyPalette = gMonShinyPalette_Horrifeel,
        .iconSprite = gMonIcon_Horrifeel,
        .iconPalIndex = 2,
        //learnsets
        .levelUpLearnset = sHorrifeelLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        },

    //P_FAMILY_WOOPEEL

    //P_FAMILY_CATERPILE

    [SPECIES_CATERPILE] =
    {
        .baseHP        = 40,
        .baseAttack    = 20,
        .baseDefense   = 20,
        .baseSpAttack  = 50,
        .baseSpDefense = 40,
        .baseSpeed     = 30,
        .types = MON_TYPES(TYPE_BUG, TYPE_ELECTRIC),
        .catchRate = 255,
        .expYield = 42,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = { ABILITY_SWARM, ABILITY_STATIC, ABILITY_ILLUMINATE },
        
        .speciesName = _("Caterpile"),
        .categoryName = _("Ver Pile"),
        .height = 3.5,
        .weight = 30,
        //data
        .evYield_SpAttack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //Ces insectes branchent leurs antennes en forme de câble à des arbres pour s'y connecter et charger leurs énergie. 
            "Ces insectes branchent leurs antennes\n"
            "en forme de câble à des arbres pour \n"
            "s'y connecter et charger leurs énergie."),
        //.natDexNum = NATIONAL_DEX_CATERPILE,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Caterpile,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
         
        .backPic = gMonBackPic_Caterpile,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Caterpile,
        .shinyPalette = gMonShinyPalette_Caterpile,
        .iconSprite = gMonIcon_Caterpile,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sCaterpileLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 15, SPECIES_COCAMPER}),
    },

    [SPECIES_COCAMPER] =
    {
        .baseHP        = 30,
        .baseAttack    = 10,
        .baseDefense   = 60,
        .baseSpAttack  = 40,
        .baseSpDefense = 80,
        .baseSpeed     = 20,
        .types = MON_TYPES(TYPE_BUG, TYPE_ELECTRIC),
        .catchRate = 140,
        .expYield = 75,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = { ABILITY_SWARM, ABILITY_STATIC, ABILITY_ILLUMINATE },
        
        .speciesName = _("Cocamper"),
        .categoryName = _("Générateur"),
        .height = 5,
        .weight = 100,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //Les Comcamper sont de petites batteries sur pattes, elles sont capables de délivrer de l'électricité jusqu'à 5000volts.
            "Les Comcamper sont de petites batteries\n"
            "sur pattes, elles sont capables de\n"
            "délivrer de l'électricité jusqu'à" 
            "5000 volts"),
        //.natDexNum = NATIONAL_DEX_COCAMPER,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Cocamper,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Cocamper,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cocamper,
        .shinyPalette = gMonShinyPalette_Cocamper,
        .iconSprite = gMonIcon_Cocamper,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sCocamperLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 23, SPECIES_LAMPIPOSA}),
    },

    [SPECIES_LAMPIPOSA] =
    {
        .baseHP        = 80,
        .baseAttack    = 60,
        .baseDefense   = 40,
        .baseSpAttack  = 115,
        .baseSpDefense = 102,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_BUG, TYPE_ELECTRIC),
        .catchRate = 100,
        .expYield = 179,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE, ABILITY_ILLUMINATE },
        
        .speciesName = _("Lampiposa"),
        .categoryName = _("Mite Lumière"),
        .height = 16,
        .weight = 400,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            //On dit que c'est grâce au pouvoir que Lampiposa possède, a savoir la génération de la lumière que la fibre optique a pu voir le jour dans nos ménages.
            "On dit que c'est grâce au pouvoir que\n"
            "Lampiposa possède, a savoir la génération\n"
            "de la lumière que la fibre optique a pu\n"
            "voir le jour dans nos ménages."),
        //.natDexNum = NATIONAL_DEX_LAMPIPOSA,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Lampiposa,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Lampiposa,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Lampiposa,
        .shinyPalette = gMonShinyPalette_Lampiposa,
        .iconSprite = gMonIcon_Lampiposa,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sLampiposaLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_CATERPILE

    //P_FAMILY_SCARABEBE

    [SPECIES_SCARABEBE] =
    {
        .baseHP        = 20,
        .baseAttack    = 58,
        .baseDefense   = 22,
        .baseSpAttack  = 45,
        .baseSpDefense = 33,
        .baseSpeed     = 89,
        .types = MON_TYPES(TYPE_BUG, TYPE_STEEL),
        .catchRate = 255,
        .expYield = 50,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {  ABILITY_SWARM, ABILITY_SHELL_ARMOR, ABILITY_WEAK_ARMOR },
        
        .speciesName = _("Scarabébé"),
        .categoryName = _("Pion"),
        .height = 2,
        .weight = 40,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        //.natDexNum = NATIONAL_DEX_SCARABEBE,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Scarabebe,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
         
        .backPic = gMonBackPic_Scarabebe,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Scarabebe,
        .shinyPalette = gMonShinyPalette_Scarabebe,
        .iconSprite = gMonIcon_Scarabebe,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sScarabebeLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 15, SPECIES_SCARACIER}),
    },

    [SPECIES_SCARACIER] =
    {
        .baseHP        = 65,
        .baseAttack    = 80,
        .baseDefense   = 100,
        .baseSpAttack  = 48,
        .baseSpDefense = 55,
        .baseSpeed     = 71,
        .types = MON_TYPES(TYPE_BUG, TYPE_STEEL),
        .catchRate = 127,
        .expYield = 101,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = { ABILITY_SWARM, ABILITY_SHELL_ARMOR, ABILITY_WEAK_ARMOR },
        
        .speciesName = _("Scaracier"),
        .categoryName = _("Chariot"),
        .height = 3.5,
        .weight = 200,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        //.natDexNum = NATIONAL_DEX_SCARACIER,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Scaracier,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Scaracier,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Scaracier,
        .shinyPalette = gMonShinyPalette_Scaracier,
        .iconSprite = gMonIcon_Scaracier,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sScaracierLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_METAL_COAT, SPECIES_SCABUTO}),
    },

    [SPECIES_SCABUTO] =
    {
        .baseHP        = 80,
        .baseAttack    = 115,
        .baseDefense   = 115,
        .baseSpAttack  = 80,
        .baseSpDefense = 65,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_BUG, TYPE_STEEL),
        .catchRate = 35,
        .expYield = 250,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = { ABILITY_SWARM, ABILITY_SHELL_ARMOR, ABILITY_SUPREME_OVERLORD },
        
        .speciesName = _("Scabuto"),
        .categoryName = _("Roi Regnant"),
        .height = 11,
        .weight = 1000,
        //data
        .evYield_Attack = 2,
        .evYield_Defense = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        //.natDexNum = NATIONAL_DEX_SCABUTO,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Scabuto,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Scabuto,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Scabuto,
        .shinyPalette = gMonShinyPalette_Scabuto,
        .iconSprite = gMonIcon_Scabuto,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sScabutoLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SCARABEBE

    //P_FAMILY_FUKUNNY

    [SPECIES_FUKUNNY] =
    {
        .baseHP        = 65,
        .baseAttack    = 32,
        .baseDefense   = 35,
        .baseSpAttack  = 32,
        .baseSpDefense = 35,
        .baseSpeed     = 67,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ICE),
        .catchRate = 255,
        .expYield = 48,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = { ABILITY_RUN_AWAY, ABILITY_ICE_BODY, ABILITY_SNOW_CLOAK },
        
        .speciesName = _("Fukunny"),
        .categoryName = _("Lapin Mochi"),
        .height = 4,
        .weight = 10,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        //.natDexNum = NATIONAL_DEX_FUKUNNY,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Fukunny,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Fukunny,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Fukunny,
        .shinyPalette = gMonShinyPalette_Fukunny,
        .iconSprite = gMonIcon_Fukunny,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sFukunnyLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_USAGUNNY}),
    },

    [SPECIES_USAGUNNY] =
    {
        .baseHP        = 71,
        .baseAttack    = 68,
        .baseDefense   = 57,
        .baseSpAttack  = 55,
        .baseSpDefense = 52,
        .baseSpeed     = 52,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ICE),
        .catchRate = 127,
        .expYield = 130,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = { ABILITY_RUN_AWAY, ABILITY_ICE_BODY, ABILITY_SNOW_CLOAK },
        
        .speciesName = _("Usagunny"),
        .categoryName = _("Gros Lapin"),
        .height = 11,
        .weight = 800,
        //data
        .evYield_HP = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        //.natDexNum = NATIONAL_DEX_USAGUNNY,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Usagunny,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Usagunny,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Usagunny,
        .shinyPalette = gMonShinyPalette_Usagunny,
        .iconSprite = gMonIcon_Usagunny,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sUsagunnyLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 31, SPECIES_YUKIGORI}),
    },

    [SPECIES_YUKIGORI] =
    {
        .baseHP        = 87,
        .baseAttack    = 85,
        .baseDefense   = 70,
        .baseSpAttack  = 95,
        .baseSpDefense = 76,
        .baseSpeed     = 95,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ICE),
        .catchRate = 100,
        .expYield = 203,
        
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = { ABILITY_SNOW_CLOAK, ABILITY_THICK_FAT, ABILITY_GORILLA_TACTICS },
        
        .speciesName = _("Yukigori"),
        .categoryName = _("LapinGorille"),
        .height = 19,
        .weight = 2510,
        //data
        .evYield_Speed = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        //.natDexNum = NATIONAL_DEX_YUKIGORI,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Yukigori,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Yukigori,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Yukigori,
        .shinyPalette = gMonShinyPalette_Yukigori,
        .iconSprite = gMonIcon_Yukigori,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sYukigoriLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
    },

    //P_FAMILY_FUKUNNY

    // P_FAMILY_GRALIBRI
    /*
    [SPECIES_GRALIBRI] =
    {
        .baseHP        = 40,
        .baseAttack    = 67,
        .baseDefense   = 48,
        .baseSpAttack  = 29,
        .baseSpDefense = 35,
        .baseSpeed     = 73,
        .types = MON_TYPES(TYPE_FLYING, TYPE_ROCK),
        .catchRate = 255,
        .expYield = 80,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = { ABILITY_KEEN_EYE, ABILITY_INNER_FOCUS, ABILITY_RUN_AWAY },
        
        .speciesName = _("Gralibri"),
        .categoryName = _("Oizo Granite"),
        .height = 3,
        .weight = 50,
        //data
        .evYield_Attack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_GRALIBRI,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Gralibri,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
         
        .backPic = gMonBackPic_Gralibri,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Gralibri,
        .shinyPalette = gMonShinyPalette_Gralibri,
        .iconSprite = gMonIcon_Gralibri,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_STALIBRI}),
    },

    [SPECIES_STALIBRI] =
    {
        .baseHP        = 53,
        .baseAttack    = 96,
        .baseDefense   = 75,
        .baseSpAttack  = 47,
        .baseSpDefense = 52,
        .baseSpeed     = 140,
        .types = MON_TYPES(TYPE_FLYING, TYPE_ROCK),
        .catchRate = 127,
        .expYield = 140,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = { ABILITY_KEEN_EYE, ABILITY_INNER_FOCUS, ABILITY_RUN_AWAY },
        
        .speciesName = _("Stalibri"),
        .categoryName = _("Stalactite"),
        .height = 14,
        .weight = 500,
        //data
        .evYield_Speed = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_STALIBRI,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Stalibri,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
         
        .backPic = gMonBackPic_Stalibri,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Stalibri,
        .shinyPalette = gMonShinyPalette_Stalibri,
        .iconSprite = gMonIcon_Stalibri,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 37, SPECIES_ZARDOPIUM}),
    },

    [SPECIES_ZARDOPIUM] =
    {
        .baseHP        = 89,
        .baseAttack    = 90,
        .baseDefense   = 75,
        .baseSpAttack  = 104,
        .baseSpDefense = 95,
        .baseSpeed     = 74,
        .types = MON_TYPES(TYPE_FLYING, TYPE_ROCK),
        .catchRate = 50,
        .expYield = 197,
        
        .genderRatio = PERCENT_FEMALE(50), 
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_OVERCOAT, ABILITY_DANCER, ABILITY_FUR_COAT },
        
        .speciesName = _("Zardopium"),
        .categoryName = _("Casanier"),
        .height = 23.9,
        .weight = 1500,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_ZARDOPIUM,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Zardopium,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Zardopium,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Zardopium,
        .shinyPalette = gMonShinyPalette_Zardopium,
        .iconSprite = gMonIcon_Zardopium,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
    },

    //P_FAMILY_GRALIBRI

    //P_FAMILY_STALLA

    [SPECIES_STALLA] =
    {
        .baseHP        = 40,
        .baseAttack    = 10,
        .baseDefense   = 13,
        .baseSpAttack  = 65,
        .baseSpDefense = 32,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_ICE),
        .catchRate = 180,
        .expYield = 64,
        
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SNOW_WARNING, ABILITY_ICE_BODY, /*ABILITY_CRISTALINE*},
        
        .speciesName = _("Stalla"),
        .categoryName = _("Cristal"),
        .height = 7,
        .weight = 10,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_STALLA,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Stalla,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .enemyMonElevation = 14,
         
        .backPic = gMonBackPic_Stalla,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Stalla,
        .shinyPalette = gMonShinyPalette_Stalla,
        .iconSprite = gMonIcon_Stalla,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_STARLING}),
    },

    [SPECIES_STARLING] =
    {
        .baseHP        = 71,
        .baseAttack    = 30,
        .baseDefense   = 30,
        .baseSpAttack  = 90,
        .baseSpDefense = 81,
        .baseSpeed     = 95,
        .types = MON_TYPES(TYPE_ICE, TYPE_FAIRY),
        .catchRate = 127,
        .expYield = 139,
        
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SNOW_WARNING, ABILITY_ICE_BODY, /*ABILITY_CRISTALINE*},
        
        .speciesName = _("Starling"),
        .categoryName = _("Nourrice"),
        .height = 11,
        .weight = 50,
        //data
        .evYield_Speed = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_STARLING,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Starling,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Starling,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Starling,
        .shinyPalette = gMonShinyPalette_Starling,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_GLADIVA}),
    },

    [SPECIES_GLADIVA] =
    {
        .baseHP        = 82,
        .baseAttack    = 50,
        .baseDefense   = 67,
        .baseSpAttack  = 107,
        .baseSpDefense = 110,
        .baseSpeed     = 117,
        .types = MON_TYPES(TYPE_ICE, TYPE_FAIRY),
        .catchRate = 90,
        .expYield = 241,
        
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SNOW_WARNING, ABILITY_ICE_BODY, /*ABILITY_CRISTALINE*},
        
        .speciesName = _("Gladiva"),
        .categoryName = _("Diva"),
        .height = 16,
        .weight = 550,
        //data
        .evYield_Speed = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_GLADIVA,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Gladiva,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Gladiva,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Gladiva,
        .shinyPalette = gMonShinyPalette_Gladiva,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_STALLA

    //P_FAMILY_ZAPEK

    [SPECIES_ZAPEK] =
    {
        .baseHP        = 30,
        .baseAttack    = 40,
        .baseDefense   = 40,
        .baseSpAttack  = 50,
        .baseSpDefense = 30,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_FLYING, TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 42,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FLUCTUATING,
        
        .abilities = {ABILITY_PICKUP, ABILITY_BIG_PECKS, ABILITY_MOLD_BREAKER},
        
        .speciesName = _("Zapek"),
        .categoryName = _("Piou Piou"),
        .height = 1,
        .weight = 10,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_DRAGON),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_ZAPEK,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Zapek,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Zapek,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Zapek,
        .shinyPalette = gMonShinyPalette_Zapek,
        .iconSprite = gMonIcon_Zapek,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_PIKORAGE}),
    },

    [SPECIES_PIKORAGE] =
    {
        .baseHP        = 60,
        .baseAttack    = 80,
        .baseDefense   = 60,
        .baseSpAttack  = 85,
        .baseSpDefense = 40,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_FLYING, TYPE_ELECTRIC),
        .catchRate = 127,
        .expYield = 127,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FLUCTUATING,
        
        .abilities = {ABILITY_PICKUP, ABILITY_BIG_PECKS, ABILITY_MOLD_BREAKER},
        
        .speciesName = _("Pikorage"),
        .categoryName = _("Calopsitte"),
        .height = 15,
        .weight = 170,
        //data
        .evYield_Speed = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_DRAGON),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .natDexNum = NATIONAL_DEX_PIKORAGE,
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Pikorage,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Pikorage,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pikorage,
        .shinyPalette = gMonShinyPalette_Pikorage,
        .iconSprite = gMonIcon_Pikorage,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_SHINY_STONE, SPECIES_COCKALYPSE}),
    },

    [SPECIES_COCKALYPSE] =
    {
        .baseHP        = 100,
        .baseAttack    = 130,
        .baseDefense   = 95,
        .baseSpAttack  = 110,
        .baseSpDefense = 65,
        .baseSpeed     = 100,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ELECTRIC),
        .catchRate = 20,
        .expYield = 250,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FLUCTUATING,
        
        .abilities = {/*ABILITY_PIKA_CLIMAT, ABILITY_NONE,* ABILITY_MOLD_BREAKER},
        
        .speciesName = _("Cockalypse"),
        .categoryName = _("Orage"),
        .height = 30,
        .weight = 2100,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_DRAGON),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_COCKALYPSE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Cockalypse,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Cockalypse,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cockalypse,
        .shinyPalette = gMonShinyPalette_Cockalypse,
        .iconSprite = gMonIcon_Cockalypse,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_ZAPEK

    //P_FAMILY_CAVIACHAT

    [SPECIES_CAVIACHAT] =
    {
        .baseHP        = 59,
        .baseAttack    = 5,
        .baseDefense   = 42,
        .baseSpAttack  = 30,
        .baseSpDefense = 42,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_WATER),
        .catchRate = 255,
        .expYield = 33,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_OVERCOAT, ABILITY_NONE,  ABILITY_STORM_DRAIN},
        
        .speciesName = _("Caviachat"),
        .categoryName = _("Caviar"),
        .height = 1,
        .weight = 30,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_CAVIACHAT,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Caviachat,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Caviachat,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Caviachat,
        .shinyPalette = gMonShinyPalette_Caviachat,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 14, SPECIES_CALIKEAU}),
    },

    [SPECIES_CALIKEAU] =
    {
        .baseHP        = 79,
        .baseAttack    = 65,
        .baseDefense   = 65,
        .baseSpAttack  = 65,
        .baseSpDefense = 65,
        .baseSpeed     = 72,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_WATER),
        .catchRate = 127,
        .expYield = 142,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_INTIMIDATE, ABILITY_TOUGH_CLAWS, ABILITY_STORM_DRAIN},
        
        .speciesName = _("Calikeau"),
        .categoryName = _("Poisson Chat"),
        .height = 8,
        .weight = 200,
        //data
        .evYield_HP = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_CALIKEAU,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Calikeau,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Calikeau,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Calikeau,
        .shinyPalette = gMonShinyPalette_Calikeau,
        .iconSprite = gMonIcon_Calikeau,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 33, SPECIES_NAUTICAT}),
    },

    [SPECIES_NAUTICAT] =
    {
        .baseHP        = 99,
        .baseAttack    = 70,
        .baseDefense   = 77,
        .baseSpAttack  = 77,
        .baseSpDefense = 70,
        .baseSpeed     = 107,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_WATER),
        .catchRate = 100,
        .expYield = 209,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_INTIMIDATE, ABILITY_TOUGH_CLAWS, ABILITY_STORM_DRAIN},
        
        .speciesName = _("Nauticat"),
        .categoryName = _("Chat Marin"),
        .height = 26,
        .weight = 1500,
        //data
        .evYield_Speed = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NAUTICAT,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Nauticat,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Nauticat,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Nauticat,
        .shinyPalette = gMonShinyPalette_Nauticat,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_CAVIACHAT

    //P_FAMILY_PLANKTEUY

    [SPECIES_PLANKTEUY] =
    {
        .baseHP        = 59,
        .baseAttack    = 33,
        .baseDefense   = 55,
        .baseSpAttack  = 64,
        .baseSpDefense = 83,
        .baseSpeed     = 56,
        .types = MON_TYPES(TYPE_GRASS, TYPE_WATER),
        .catchRate = 255,
        .expYield = 100,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_LEAF_GUARD, ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        
        .speciesName = _("Plankteuy"),
        .categoryName = _("Plancton"),
        .height = 1,
        .weight = 1,
        //data
        .evYield_SpDefense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_WATER_1),
        .bodyColor = BODY_COLOR_GREEN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PLANKTEUY,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Plankteuy,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Plankteuy,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Plankteuy,
        .shinyPalette = gMonShinyPalette_Plankteuy,
        .iconSprite = gMonIcon_Plankteuy,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_PLANKTEUY

    //P_FAMILY_MELODIE

    [SPECIES_MELODIE] =
    {
        .baseHP        = 60,
        .baseAttack    = 43,
        .baseDefense   = 45,
        .baseSpAttack  = 68,
        .baseSpDefense = 61,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_DARK),
        .catchRate = 180,
        .expYield = 86,
        
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_CURSED_BODY, ABILITY_SOUNDPROOF, ABILITY_PUNK_ROCK},
        
        .speciesName = _("Melodie"),
        .categoryName = _("Dramaturge"),
        .height = 4,
        .weight = 10,
        //data
        .evYield_SpAttack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_MELODIE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Melodie,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Melodie,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Melodie,
        .shinyPalette = gMonShinyPalette_Melodie,
        .iconSprite = gMonIcon_Melodie,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_FRIENDSHIP, 0, SPECIES_MELODRAME}),
    },

    [SPECIES_MELODRAME] =
    {
        .baseHP        = 82,
        .baseAttack    = 50,
        .baseDefense   = 75,
        .baseSpAttack  = 103,
        .baseSpDefense = 100,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_DARK),
        .catchRate = 100,
        .expYield = 176,
        
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_CURSED_BODY, ABILITY_SOUNDPROOF, ABILITY_PUNK_ROCK},
        
        .speciesName = _("Melodrame"),
        .categoryName = _("Vedette"),
        .height = 14.8,
        .weight = 30,
        //data
        .evYield_SpAttack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_MELODRAME,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Melodrame,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Melodrame,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Melodrame,
        .shinyPalette = gMonShinyPalette_Melodrame,
        .iconSprite = gMonIcon_Melodrame,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,

    },

    //P_FAMILY_MELODIE

    //P_FAMILY_BLIPPER

    [SPECIES_BLIPPER] =
    {
        .baseHP        = 44,
        .baseAttack    = 45,
        .baseDefense   = 53,
        .baseSpAttack  = 30,
        .baseSpDefense = 55,
        .baseSpeed     = 33,
        .types = MON_TYPES(TYPE_BUG, TYPE_PSYCHIC),

        .catchRate = 180,
        .expYield = 42,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_FOREWARN, ABILITY_LEVITATE, ABILITY_TELEPATHY },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Bipper"),
        .categoryName = _("Nuisance"),
        .height = 1,
        .weight = 8,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_COPESPINE}),
        .natDexNum = NATIONAL_DEX_BLIPPER,
        
        .cryId = CRY_NONE,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Blipper,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Blipper,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Blipper,
        .shinyPalette = gMonShinyPalette_Blipper,
        .iconSprite = gMonIcon_Blipper,
        .iconPalIndex = 0,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
    },

    [SPECIES_COPESPINE] =
    {
        .baseHP        = 64,
        .baseAttack    = 65,
        .baseDefense   = 88,
        .baseSpAttack  = 53,
        .baseSpDefense = 61,
        .baseSpeed     = 44,
        .types = MON_TYPES(TYPE_BUG, TYPE_PSYCHIC),

        .catchRate = 140,
        .expYield = 100,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_FOREWARN, ABILITY_LEVITATE, ABILITY_TELEPATHY },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Copespine"),
        .categoryName = _("Agrippic"),
        .height = 8,
        .weight = 50,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 32, SPECIES_BLOPELLER}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_COPESPINE,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Copespine,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Copespine,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Copespine,
        .shinyPalette = gMonShinyPalette_Copespine,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,

    },

    [SPECIES_BLOPELLER] =
    {
        .baseHP        = 85,
        .baseAttack    = 96,
        .baseDefense   = 110,
        .baseSpAttack  = 84,
        .baseSpDefense = 84,
        .baseSpeed     = 55,
        .types = MON_TYPES(TYPE_BUG, TYPE_PSYCHIC),

        .catchRate = 90,
        .evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_FOREWARN, ABILITY_LEVITATE, ABILITY_TELEPATHY },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Coleangios"),
        .categoryName = _("Pétalinsect"),
        .height = 17,
        .weight = 1000,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_BLOPELLER,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Blopeller,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Blopeller,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Blopeller,
        .shinyPalette = gMonShinyPalette_Blopeller,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_BLIPPER

    //P_FAMILY_TAUPETI

    [SPECIES_TAUPETI] =
    {
        .baseHP        = 50,
        .baseAttack    = 40,
        .baseDefense   = 65,
        .baseSpAttack  = 15,
        .baseSpDefense = 30,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_GROUND),
        .catchRate = 205,
        .expYield = 97,
        
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_RUN_AWAY, ABILITY_OBLIVIOUS, ABILITY_SAND_RUSH},
        
        .speciesName = _("Taupéti"),
        .categoryName = _("Taupe"),
        .height = 5,
        .weight = 300,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TAUPETI,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Taupeti,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Taupeti,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Taupeti,
        .shinyPalette = gMonShinyPalette_Taupeti,
        .iconSprite = gMonIcon_Taupeti,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_TAUPASSAGE}),
    },

    [SPECIES_TAUPASSAGE] =
    {
        .baseHP        = 40,
        .baseAttack    = 80,
        .baseDefense   = 87,
        .baseSpAttack  = 35,
        .baseSpDefense = 49,
        .baseSpeed     = 53,
        .types = MON_TYPES(TYPE_GROUND, TYPE_FIGHTING),
        .catchRate = 127,
        .expYield = 103,
        
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_TRUANT, ABILITY_STALL, ABILITY_OWN_TEMPO},
        
        .speciesName = _("Taupassage"),
        .categoryName = _("Grosse Taupe"),
        .height = 8,
        .weight = 700,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TAUPASSAGE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM_HOLD, ITEM_PROTECTOR, SPECIES_TAUPERE}),
    },

    [SPECIES_TAUPERE] =
    {
        .baseHP        = 69,
        .baseAttack    = 140,
        .baseDefense   = 100,
        .baseSpAttack  = 40,
        .baseSpDefense = 79,
        .baseSpeed     = 72,
        .types = MON_TYPES(TYPE_GROUND, TYPE_FIGHTING),
        .catchRate = 80,
        .expYield = 199,
        
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_EARLY_BIRD, ABILITY_GUTS, ABILITY_SAND_RUSH},
        
        .speciesName = _("Taupère"),
        .categoryName = _("Vétéran"),
        .height = 16,
        .weight = 950,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TAUPERE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_TAUPETI

    //P_FAMILY_GERBUZZ

    [SPECIES_GERBUZZ] =
    {
        .baseHP        = 40,
        .baseAttack    = 40,
        .baseDefense   = 45,
        .baseSpAttack  = 80,
        .baseSpDefense = 45,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 190,
        .expYield = 76,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_STATIC, ABILITY_SAND_RUSH, ABILITY_LIGHTNING_ROD},
        
        .speciesName = _("Gerbuzz"),
        .categoryName = _("Gerbille"),
        .height = 2,
        .weight = 12,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_GERBUZZ,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Gerbuzz,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Gerbuzz,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Gerbuzz,
        .shinyPalette = gMonShinyPalette_Gerbuzz,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_THUNDER_STONE, SPECIES_TESLANTEN}),
    },

    [SPECIES_TESLANTEN] =
    {
        .baseHP        = 70,
        .baseAttack    = 70,
        .baseDefense   = 60,
        .baseSpAttack  = 100,
        .baseSpDefense = 70,
        .baseSpeed     = 115,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 100,
        .expYield = 151,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_STATIC, ABILITY_SAND_RUSH, ABILITY_LIGHTNING_ROD},
        
        .speciesName = _("Teslanten"),
        .categoryName = _("Gerbille"),
        .height = 16,
        .weight = 300,
        //data
        .evYield_Speed = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TESLANTEN,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_GERBUZZ

    //P_FAMILY_GALEMIMI

    [SPECIES_GALEMIMI] =
    {
        .baseHP        = 40,
        .baseAttack    = 65,
        .baseDefense   = 90,
        .baseSpAttack  = 30,
        .baseSpDefense = 20,
        .baseSpeed     = 31,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 205,
        .expYield = 58,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_STURDY, ABILITY_ROUGH_SKIN, ABILITY_SOUNDPROOF},
        
        .speciesName = _("Galemimi"),
        .categoryName = _("Galet"),
        .height = 2,
        .weight = 100,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_GALEMIMI,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Galemimi,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
         
        .backPic = gMonBackPic_Galemimi,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Galemimi,
        .shinyPalette = gMonShinyPalette_Galemimi,
        .iconSprite = gMonIcon_Galemimi,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 19, SPECIES_GALEM}),
    },

    [SPECIES_GALEM] =
    {
        .baseHP        = 81,
        .baseAttack    = 73,
        .baseDefense   = 90,
        .baseSpAttack  = 61,
        .baseSpDefense = 66,
        .baseSpeed     = 46,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 127,
        .expYield = 129,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_STURDY, ABILITY_ROUGH_SKIN, ABILITY_SOUNDPROOF},
        
        .speciesName = _("Galem"),
        .categoryName = _("Galet Golem"),
        .height = 15,
        .weight = 1000,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_GALEM,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Galem,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Galem,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Galem,
        .shinyPalette = gMonShinyPalette_Galem,
        .iconSprite = gMonIcon_Galem,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 37, SPECIES_WARDELITH}),
    },

    [SPECIES_WARDELITH] =
    {
        .baseHP        = 95,
        .baseAttack    = 90,
        .baseDefense   = 90,
        .baseSpAttack  = 90,
        .baseSpDefense = 100,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 70,
        .expYield = 167,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_STURDY, ABILITY_ROUGH_SKIN, ABILITY_SOUNDPROOF},
        
        .speciesName = _("Wardelith"),
        .categoryName = _("Gardien"),
        .height = 29,
        .weight = 3000,
        //data
        .evYield_SpDefense = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_WARDELITH,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_GALEMIMI

    //P_FAMILY_GROUNDER

    [SPECIES_GROUNDER] =
    {
        .baseHP        = 90,
        .baseAttack    = 93,
        .baseDefense   = 132,
        .baseSpAttack  = 77,
        .baseSpDefense = 58,
        .baseSpeed     = 43,
        .types = MON_TYPES(TYPE_GROUND),
        .catchRate = 100,
        .expYield = 180,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_ARENA_TRAP, ABILITY_SHADOW_TAG, ABILITY_COLOR_CHANGE},
        
        .speciesName = _("Grounder"),
        .categoryName = _("Terrain"),
        .height = 9999,
        .weight = 9999,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BLACK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_GROUNDER,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Grounder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
         
        .backPic = gMonBackPic_Grounder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Grounder,
        .shinyPalette = gMonShinyPalette_Grounder,
        .iconSprite = gMonIcon_Grounder,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_GROUDER

    //P_FAMILY_SNIFOUY

    [SPECIES_SNIFOUY] =
    {
        .baseHP        = 50,
        .baseAttack    = 30,
        .baseDefense   = 30,
        .baseSpAttack  = 40,
        .baseSpDefense = 50,
        .baseSpeed     = 30,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 235,
        .expYield = 66,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_ANTICIPATION ,ABILITY_HUGE_POWER, ABILITY_RATTLED},
        
        .speciesName = _("Snifouy"),
        .categoryName = _("Chouineur"),
        .height = 6,
        .weight = 40,
        //data
        .evYield_HP = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_SNIFOUY,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Snifouy,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Snifouy,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Snifouy,
        .shinyPalette = gMonShinyPalette_Snifouy,
        .iconSprite = gMonIcon_Snifouy,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_FRIENDSHIP, 0, SPECIES_FISTFOUY}),
    },

    [SPECIES_FISTFOUY] =
    {
        .baseHP        = 75,
        .baseAttack    = 61,
        .baseDefense   = 86,
        .baseSpAttack  = 80,
        .baseSpDefense = 76,
        .baseSpeed     = 92,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 80,
        .expYield = 149,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_ANTICIPATION ,ABILITY_HUGE_POWER, ABILITY_RATTLED},
        
        .speciesName = _("Fistfouy"),
        .categoryName = _("Revanche"),
        .height = 14,
        .weight = 600,
        //data
        .evYield_Speed = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FISTFOUY,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SNIFOUY

    //P_FAMILY_NEKOFEE

    [SPECIES_NEKOFEE] =
    {
        .baseHP        = 80,
        .baseAttack    = 83,
        .baseDefense   = 67,
        .baseSpAttack  = 98,
        .baseSpDefense = 80,
        .baseSpeed     = 75,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_FIRE),
        .catchRate = 130,
        .expYield = 166,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_FLAME_BODY, ABILITY_NATURAL_CURE, ABILITY_FAIRY_AURA},
        
        .speciesName = _("Nekofee"),
        .categoryName = _("Chafé Latte"),
        .height = 3.2,
        .weight = 1,
        //data
        .evYield_SpAttack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NEKOFEE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Nekofee,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Nekofee,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Nekofee,
        .shinyPalette = gMonShinyPalette_Nekofee,
        .iconSprite = gMonIcon_Nekofee,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_NEKOFEE

    //P_FAMILY_PLOUFFY

    [SPECIES_PLOUFFY] =
    {
        .baseHP        = 50,
        .baseAttack    = 32,
        .baseDefense   = 30,
        .baseSpAttack  = 65,
        .baseSpDefense = 35,
        .baseSpeed     = 53,
        .types = MON_TYPES(TYPE_WATER, TYPE_PSYCHIC),
        .catchRate = 220,
        .expYield = 48,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_UNBURDEN, ABILITY_RAIN_DISH, ABILITY_MAGIC_GUARD},
        
        .speciesName = _("Plouffy"),
        .categoryName = _("Canardebain"),
        .height = 1.2,
        .weight = 5,
        //data
        .evYield_SpAttack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PLOUFFY,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Plouffy,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Plouffy,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Plouffy,
        .shinyPalette = gMonShinyPalette_Plouffy,
        .iconSprite = gMonIcon_Plouffy,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 26, SPECIES_COINQWACK}),
    },

    [SPECIES_COINQWACK] =
    {
        .baseHP        = 52,
        .baseAttack    = 66,
        .baseDefense   = 70,
        .baseSpAttack  = 92,
        .baseSpDefense = 80,
        .baseSpeed     = 53,
        .types = MON_TYPES(TYPE_WATER, TYPE_PSYCHIC),
        .catchRate = 127,
        .expYield = 133,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_UNBURDEN, ABILITY_RAIN_DISH, ABILITY_MAGIC_GUARD},
        
        .speciesName = _("Coinqwack"),
        .categoryName = _("Canardebain"),
        .height = 5,
        .weight = 100,
        //data
        .evYield_SpAttack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_COINQWACK,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Coinqwack,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Coinqwack,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Coinqwack,
        .shinyPalette = gMonShinyPalette_Coinqwack,
        .iconSprite = gMonIcon_Coinqwack,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 33, SPECIES_COLBOUEE}),
    },

    [SPECIES_COLBOUEE] =
    {
        .baseHP        = 60,
        .baseAttack    = 80,
        .baseDefense   = 80,
        .baseSpAttack  = 104,
        .baseSpDefense = 105,
        .baseSpeed     = 71,
        .types = MON_TYPES(TYPE_WATER, TYPE_PSYCHIC),
        .catchRate = 100,
        .expYield = 178,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_UNBURDEN, ABILITY_RAIN_DISH, ABILITY_MAGIC_GUARD},
        
        .speciesName = _("Colbouée"),
        .categoryName = _("Canardebain"),
        .height = 13,
        .weight = 280,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_COLBOUEE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Colbouee,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Colbouee,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Colbouee,
        .shinyPalette = gMonShinyPalette_Colbouee,
        .iconSprite = gMonIcon_Colbouee,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_PLOUFFY

    //P_FAMILY_HEMOGLEZARD

    [SPECIES_HEMOGLEZAR] =
    {
        .baseHP        = 52,
        .baseAttack    = 41,
        .baseDefense   = 60,
        .baseSpAttack  = 85,
        .baseSpDefense = 46,
        .baseSpeed     = 71,
        .types = MON_TYPES(TYPE_GROUND, TYPE_FIRE),
        .catchRate = 225,
        .expYield = 87,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {/*ABILITY_THERMOFRAPPE,* ABILITY_DRY_SKIN, ABILITY_SAND_VEIL},
        
        .speciesName = _("Hemoglézar"),
        .categoryName = _("Sang Lézard"),
        .height = 4.5,
        .weight = 50,
        //data
        .evYield_SpAttack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_DRAGON),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_HEMOGLEZAR,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 43, SPECIES_SANGLODON}),
    },

    [SPECIES_SANGLODON] =
    {
        .baseHP        = 70,
        .baseAttack    = 116,
        .baseDefense   = 82,
        .baseSpAttack  = 92,
        .baseSpDefense = 82,
        .baseSpeed     = 81,
        .types = MON_TYPES(TYPE_GROUND, TYPE_FIRE),
        .catchRate = 35,
        .expYield = 193,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {/*ABILITY_THERMOFRAPPE,* ABILITY_DRY_SKIN, ABILITY_SAND_VEIL},
        
        .speciesName = _("Sanglodon"),
        .categoryName = _("Bouillant"),
        .height = 18,
        .weight = 800,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_DRAGON),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_SANGLODON,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Sanglodon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Sanglodon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Sanglodon,
        .shinyPalette = gMonShinyPalette_Sanglodon,
        .iconSprite = gMonIcon_Sanglodon,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_HEMOGLEZARD

    //P_FAMILY_COCOQUILLE

    [SPECIES_COCOQUILLE] =
    {
        .baseHP        = 35,
        .baseAttack    = 76,
        .baseDefense   = 100,
        .baseSpAttack  = 25,
        .baseSpDefense = 44,
        .baseSpeed     = 24,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ROCK),
        .catchRate = 205,
        .expYield = 79,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_PICKUP, ABILITY_BATTLE_ARMOR},
        
        .speciesName = _("Cocoquille"),
        .categoryName = _("Coco Crabe"),
        .height = 3,
        .weight = 20,
        //data
        .evYield_Defense = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .bodyColor = BODY_COLOR_GREEN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_COCOQUILLE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_PALMYPINCE}),
    },

    [SPECIES_PALMYPINCE] =
    {
        .baseHP        = 57,
        .baseAttack    = 101,
        .baseDefense   = 127,
        .baseSpAttack  = 58,
        .baseSpDefense = 64,
        .baseSpeed     = 93,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ROCK),
        .catchRate = 90,
        .expYield = 145,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_PICKUP/*, ABILITY_FORCE_AQUA*},
        
        .speciesName = _("Palmypince"),
        .categoryName = _("Coco Pince"),
        .height = 10,
        .weight = 500,
        //data
        .evYield_Defense = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PALMYPINCE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_COCOQUILLE

    //P_FAMILY_PLOPETIT

    [SPECIES_PLOPETIT] = 
    {
        .baseHP        = 70,
        .baseAttack    = 30,
        .baseDefense   = 60,
        .baseSpAttack  = 30,
        .baseSpDefense = 60,
        .baseSpeed     = 20,
        .types = MON_TYPES(TYPE_BUG),

        .catchRate = 200,
        .expYield = 50,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Plopetit"),
        .categoryName = _("Bullarve"),
        .height = 5,
        .weight = 40,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 28, SPECIES_BUBULLON}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PLOPETIT,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_BUBULLON] = 
    {
        .baseHP        = 88,
        .baseAttack    = 75,
        .baseDefense   = 90,
        .baseSpAttack  = 90,
        .baseSpDefense = 95,
        .baseSpeed     = 72,
        .types = MON_TYPES(TYPE_BUG, TYPE_WATER),

        .catchRate = 100,
        .expYield = 164,
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_WATER_BUBBLE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Bubullon"),
        .categoryName = _("Bullailes"),
        .height = 9,
        .weight = 750,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_BUBULLON,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_PLOPETIT

    //P_FAMILY_FEUVALIER

    [SPECIES_FEUVALIER] =
    {
        .baseHP        = 30,
        .baseAttack    = 22,
        .baseDefense   = 44,
        .baseSpAttack  = 90,
        .baseSpDefense = 32,
        .baseSpeed     = 100,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 195,
        .expYield = 68,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_LEVITATE, ABILITY_FLAME_BODY, ABILITY_GRIM_NEIGH },
        
        .speciesName = _("Feuvalier"),
        .categoryName = _("Crâne Cavale"),
        .height = 5,
        .weight = 300,
        //data
        .evYield_Speed = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FEUVALIER,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_DUSK_STONE, SPECIES_AGOHENIE}),
    },

    [SPECIES_AGOHENIE] =
    {
        .baseHP        = 61,
        .baseAttack    = 83,
        .baseDefense   = 90,
        .baseSpAttack  = 120,
        .baseSpDefense = 60,
        .baseSpeed     = 96,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GHOST),
        .catchRate = 35,
        .expYield = 199,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_LEVITATE, ABILITY_FLAME_BODY, ABILITY_GRIM_NEIGH},
        
        .speciesName = _("Agohénie"),
        .categoryName = _("Agonie"),
        .height = 20,
        .weight = 2010,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_AGOHENIE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_FEUVALIER

    //P_FAMILY_KATCHINA

    [SPECIES_KATCHINA] =
    {
        .baseHP        = 50,
        .baseAttack    = 50,
        .baseDefense   = 50,
        .baseSpAttack  = 50,
        .baseSpDefense = 50,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = 200,  
        .expYield = 66,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,   
        
        .abilities = {ABILITY_COMATOSE},
        
        .speciesName = _("Katchina"),
        .categoryName = _("Attrape Rêve"),
        .height = 6,
        .weight = 20,
        //data
        .evYield_HP = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_PINK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_KATCHINA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_MOVE, MOVE_FLYING_PRESS, SPECIES_ELKATCHINA}),
    },

    [SPECIES_ELKATCHINA] =
    {
        .baseHP        = 116,
        .baseAttack    = 81,
        .baseDefense   = 75,
        .baseSpAttack  = 115,
        .baseSpDefense = 75,
        .baseSpeed     = 55,
        .types = MON_TYPES(TYPE_PSYCHIC, TYPE_FIGHTING),
        .catchRate = 50,
        .expYield = 181,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_COMATOSE},
        
        .speciesName = _("ElKatchina"),
        .categoryName = _("Tabasse Rêve"),
        .height = 14,
        .weight = 300,
        //data
        .evYield_HP = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_PINK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_ELKATCHINA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_KATCHINA

    //P_FAMILY_ALWY

    [SPECIES_ALWY] =
    {
        .baseHP        = 43,
        .baseAttack    = 44,
        .baseDefense   = 60,
        .baseSpAttack  = 40,
        .baseSpDefense = 55,
        .baseSpeed     = 45,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GROUND),
        .catchRate = 200,
        .expYield = 59,
        
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {/*ABILITY_SKIN_CARE,* ABILITY_WATER_VEIL, ABILITY_IRON_BARBS},
        
        .speciesName = _("Alwy"),
        .categoryName = _("Aloe Vera"),
        .height = 2,
        .weight = 150,
        //data
        .evYield_Defense = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .bodyColor = BODY_COLOR_GREEN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_ALWY,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 23, SPECIES_VEROPHYLA}),
    },

    [SPECIES_VEROPHYLA] =
    {
        .baseHP        = 72,
        .baseAttack    = 76,
        .baseDefense   = 102,
        .baseSpAttack  = 40,
        .baseSpDefense = 80,
        .baseSpeed     = 45,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GROUND),
        .catchRate = 127,
        .expYield = 133,
        
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {/*ABILITY_SKIN_CARE,* ABILITY_WATER_VEIL, ABILITY_IRON_BARBS},
        
        .speciesName = _("Verophyla"),
        .categoryName = _("Aloe Vera"),
        .height = 3,
        .weight = 400,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .bodyColor = BODY_COLOR_GREEN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_VEROPHYLA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_METAL_COAT, SPECIES_VERACINA}),
    },

    [SPECIES_VERACINA] =
    {
        .baseHP        = 82,
        .baseAttack    = 79,
        .baseDefense   = 118,
        .baseSpAttack  = 91,
        .baseSpDefense = 80,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_GRASS, TYPE_STEEL),
        .catchRate = 75,
        .expYield = 173,
        
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {/*ABILITY_SKIN_CARE,* ABILITY_FILTER, ABILITY_IRON_BARBS},
        
        .speciesName = _("Veracina"),
        .categoryName = _("Aloe Vera"),
        .height = 9,
        .weight = 200,
        //data
        .evYield_Defense = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .bodyColor = BODY_COLOR_GREEN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_VERACINA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_ALWY

    //P_FAMILY_SQUALIL

    [SPECIES_SQUALIL] =
    {
        .baseHP        = 55,
        .baseAttack    = 60,
        .baseDefense   = 25,
        .baseSpAttack  = 40,
        .baseSpDefense = 55,
        .baseSpeed     = 45,
        .types = MON_TYPES(TYPE_FIRE, TYPE_WATER),
        .catchRate = 155,
        .expYield = 100,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_FLASH_FIRE, ABILITY_STRONG_JAW},
        
        .speciesName = _("Squalil"),
        .categoryName = _("Requin Lave"),
        .height = 9,
        .weight = 1000,
        //data
        .evYield_Attack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_SQUALIL,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Squalil,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Squalil,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Squalil,
        .shinyPalette = gMonShinyPalette_Squalil,
        .iconSprite = gMonIcon_Squalil,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 37, SPECIES_SQUALAVA}),
    },

    [SPECIES_SQUALAVA] =
    {
        .baseHP        = 90,
        .baseAttack    = 90,
        .baseDefense   = 55,
        .baseSpAttack  = 90,
        .baseSpDefense = 65,
        .baseSpeed     = 89,
        .types = MON_TYPES(TYPE_FIRE, TYPE_WATER),
        .catchRate = 80,
        .expYield = 166,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_FLASH_FIRE, ABILITY_STRONG_JAW},
        
        .speciesName = _("Squalava"),
        .categoryName = _("Requin Lave"),
        .height = 25,
        .weight = 3000,
        //data
        .evYield_Attack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_SQUALAVA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 50, SPECIES_MAGMALODON}/*,
                                {EVO_LEVEL, ITEM_PIERRE_MAGMA, SPECIES_MAGMALODON}*),
    },

    [SPECIES_MAGMALODON] =
    {
        .baseHP        = 110,
        .baseAttack    = 135,
        .baseDefense   = 95,
        .baseSpAttack  = 65,
        .baseSpDefense = 80,
        .baseSpeed     = 65,
        .types = MON_TYPES(TYPE_FIRE, TYPE_WATER),
        .catchRate = 35,
        .expYield = 242,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_FLASH_FIRE, ABILITY_STRONG_JAW},
        
        .speciesName = _("Magmalodon"),
        .categoryName = _("Requin Magma"),
        .height = 150,
        .weight = 9000,
        //data
        .evYield_Attack= 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_MAGMALODON,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SQUALIL

    //P_FAMILY_CHAROSABLE

    [SPECIES_CHAROSABLE] =
    {
        .baseHP        = 55,
        .baseAttack    = 50,
        .baseDefense   = 75,
        .baseSpAttack  = 48,
        .baseSpDefense = 75,
        .baseSpeed     = 55,
        .types = MON_TYPES(TYPE_FLYING, TYPE_GROUND),
        .catchRate = 170,
        .expYield = 88,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SOLAR_POWER, ABILITY_SAND_STREAM, ABILITY_SAND_RUSH},
        
        .speciesName = _("Charosable"),
        .categoryName = _("Charognard"),
        .height = 6,
        .weight = 80,
        //data
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_CHAROSABLE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 33, SPECIES_DUNESTIN}
                                /*,{EVO_ITEM, ITEM_HEMOQUEUE, SPECIES_DUNESTIN}*),
    },

    [SPECIES_DUNESTIN] =
    {
        .baseHP        = 80,
        .baseAttack    = 80,
        .baseDefense   = 120,
        .baseSpAttack  = 75,
        .baseSpDefense = 120,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_FLYING, TYPE_GROUND),
        .catchRate = 35,
        .expYield = 203,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SOLAR_POWER, ABILITY_SAND_STREAM, ABILITY_SAND_RUSH},
        
        .speciesName = _("Dunestin"),
        .categoryName = _("Embuscade"),
        .height = 25,
        .weight = 3000,
        //data
        .evYield_Defense = 2,
        .evYield_SpDefense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_DUNESTIN,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_CHAROSABLE

    //P_FAMILY_ANCAT

    [SPECIES_ANCAT] =
    {
        .baseHP        = 40,
        .baseAttack    = 88,
        .baseDefense   = 56,
        .baseSpAttack  = 55,
        .baseSpDefense = 55,
        .baseSpeed     = 96,
        .types = MON_TYPES(TYPE_GROUND, TYPE_GHOST),
        .catchRate = 170,
        .expYield = 69,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_CURSED_BODY, ABILITY_INFILTRATOR, ABILITY_SAND_STREAM},
        
        .speciesName = _("Ancat"),
        .categoryName = _("Glyfélin"),
        .height = 7,
        .weight = 110,
        //data
        .evYield_Attack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_ANCAT,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 32, SPECIES_PSALMEURTRI}),
    },

    [SPECIES_PSALMEURTRI] =
    {
        .baseHP        = 112,
        .baseAttack    = 50,
        .baseDefense   = 120,
        .baseSpAttack  = 106,
        .baseSpDefense = 55,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_GROUND, TYPE_GHOST),
        .catchRate = 25,
        .expYield = 152,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_CURSED_BODY, ABILITY_INFILTRATOR, ABILITY_SAND_STREAM},
        
        .speciesName = _("Psalmeurtri"),
        .categoryName = _("Glyfélin"),
        .height = 15,
        .weight = 10,
        //data
        .evYield_Defense = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PSALMEURTRI,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_ANCAT

    //P_FAMILY_CHEEPOUF

    [SPECIES_CHEEPOUF] = 
    {
        .baseHP        = 45,
        .baseAttack    = 45,
        .baseDefense   = 25,
        .baseSpAttack  = 65,
        .baseSpDefense = 30,
        .baseSpeed     = 55,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FIRE),

        .catchRate = 155,
        .expYield = 66,
        .evYield_SpAttack = 1,
        .genderRatio = MON_MALE,
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SHIELD_DUST, ABILITY_FLASH_FIRE, ABILITY_SURGE_SURFER},
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Cheepouf"),
        .categoryName = _("Cheetigre"),
        .height = 6.8,
        .weight = 90,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 31, SPECIES_CHEESETAH}),
        
        .cryId = CRY_NONE,
        
        .natDexNum = NATIONAL_DEX_CHEEPOUF,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Cheepouf,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Cheepouf,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Cheepouf,
        .shinyPalette = gMonShinyPalette_Cheepouf,
        .iconSprite = gMonIcon_Cheepouf,
        .iconPalIndex = 0,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    [SPECIES_CHEESETAH] = 
    {
        .baseHP        = 69,
        .baseAttack    = 117,
        .baseDefense   = 52,
        .baseSpAttack  = 99,
        .baseSpDefense = 50,
        .baseSpeed     = 132,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FIRE),

        .catchRate = 80,
        .expYield = 155,
        .evYield_Speed = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SHIELD_DUST, ABILITY_FLASH_FIRE, ABILITY_SURGE_SURFER },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Cheesetah"),
        .categoryName = _("Cheetigre"),
        .height = 14,
        .weight = 640,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        
        .natDexNum = NATIONAL_DEX_CHEESETAH,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Cheesetah,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Cheesetah,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Cheesetah,
        .shinyPalette = gMonShinyPalette_Cheesetah,
        .iconSprite = gMonIcon_Cheesetah,
        .iconPalIndex = 0,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_CHEEPOUF

    //P_FAMILY_KHEPRISUN

    [SPECIES_KHEPRISUN] = 
    {
        .baseHP        = 70,
        .baseAttack    = 70,
        .baseDefense   = 40,
        .baseSpAttack  = 150,
        .baseSpDefense = 80,
        .baseSpeed     = 20,
        .types = MON_TYPES(TYPE_FIRE, TYPE_STEEL),

        .catchRate = 80,
        .expYield = 203,
        .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_DROUGHT, ABILITY_NONE, ABILITY_LEVITATE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Khéprisun"),
        .categoryName = _("Soleil"),
        .height = 1,
        .weight = 100,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        
        .natDexNum = NATIONAL_DEX_KHEPRISUN,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_KHEPRISUN

    //P_FAMILY_MAYSUGEKI

    [SPECIES_MAYSUGEKI] = 
    {
        .baseHP        = 71,
        .baseAttack    = 121,
        .baseDefense   = 70,
        .baseSpAttack  = 61,
        .baseSpDefense = 71,
        .baseSpeed     = 117,
        .types = MON_TYPES(TYPE_WATER, TYPE_FIGHTING),

        .catchRate = 100,
        .expYield = 143,
        .evYield_Attack = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_RECKLESS, ABILITY_STEELWORKER, ABILITY_SWIFT_SWIM },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Maysugeki"),
        .categoryName = _("Dauphin"),
        .height = 20,
        .weight = 2000,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        
        .natDexNum = NATIONAL_DEX_MAYSUGEKI,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Maysugeki,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Maysugeki,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Maysugeki,
        .shinyPalette = gMonShinyPalette_Maysugeki,
        .iconSprite = gMonIcon_Maysugeki,
        .iconPalIndex = 0,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_MAYSUGEKI

    //P_FAMILY_VEROTE

    [SPECIES_VEROTE] =
    {
        .baseHP        = 53,
        .baseAttack    = 81,
        .baseDefense   = 60,
        .baseSpAttack  = 95,
        .baseSpDefense = 40,
        .baseSpeed     = 5,
        .types = MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 180,
        .expYield = 77,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_GLUTTONY,/*ABILITY_LACERATION, * ABILITY_DAMP , ABILITY_INFILTRATOR},
        
        .speciesName = _("Verote"),
        .categoryName = _("Steak"),
        .height = 7.5,
        .weight = 90,
        //data
        .evYield_SpAttack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_MONSTER),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_VEROTE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_ROTTENIA}
                                /*, {EVO_ITEM, ITEM_MAIN_PUTRIDE, SPECIES_ROTTENIA}*),
    },

    [SPECIES_ROTTENIA] =
    {
        .baseHP        = 102,
        .baseAttack    = 100,
        .baseDefense   = 86,
        .baseSpAttack  = 95,
        .baseSpDefense = 63,
        .baseSpeed     = 5,
        .types = MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 50,
        .expYield = 144,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_GLUTTONY,/*ABILITY_LACERATION, * ABILITY_DAMP , ABILITY_INFILTRATOR},
        
        .speciesName = _("Rottenia"),
        .categoryName = _("Tenia"),
        .height = 10,
        .weight = 1100,
        //data
        .evYield_HP = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_MONSTER),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_ROTTENIA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_VEROTE

    //P_FAMILY_BOH

    [SPECIES_BOH] =
    {
        .baseHP        = 24,
        .baseAttack    = 20,
        .baseDefense   = 34,
        .baseSpAttack  = 15,
        .baseSpDefense = 20,
        .baseSpeed     = 26,
        .types = MON_TYPES(TYPE_POISON),
        .catchRate = 255,
        .expYield = 30,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_STENCH, ABILITY_OBLIVIOUS, ABILITY_UNAWARE},
        
        .speciesName = _("Boh"),
        .categoryName = _("Mutant"),
        .height = 1,
        .weight = 10,
        //data
        .evYield_HP = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_BOH,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Boh,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Boh,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Boh,
        .shinyPalette = gMonShinyPalette_Boh,
        .iconSprite = gMonIcon_Boh,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_EUARK}),
    },

    [SPECIES_EUARK] =
    {
        .baseHP        = 40,
        .baseAttack    = 59,
        .baseDefense   = 35,
        .baseSpAttack  = 32,
        .baseSpDefense = 30,
        .baseSpeed     = 28,
        .types = MON_TYPES(TYPE_POISON),
        .catchRate = 140,
        .expYield = 86,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_STENCH, ABILITY_OBLIVIOUS, ABILITY_AFTERMATH},
        
        .speciesName = _("Euark"),
        .categoryName = _("Dégoutant"),
        .height = 8.9,
        .weight = 200,
        //data
        .evYield_Attack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_EUARK,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Euark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Euark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Euark,
        .shinyPalette = gMonShinyPalette_Euark,
        .iconSprite = gMonIcon_Euark,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_OHHAERK}),
    },

    [SPECIES_OHHAERK] =
    {
        .baseHP        = 95,
        .baseAttack    = 90,
        .baseDefense   = 90,
        .baseSpAttack  = 87,
        .baseSpDefense = 85,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_POISON),
        .catchRate = 70,
        .expYield = 138,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_STENCH, ABILITY_STICKY_HOLD, ABILITY_AFTERMATH},
        
        .speciesName = _("Ohhaerk"),
        .categoryName = _("Répugnant"),
        .height = 11,
        .weight = 1000,
        //data
        .evYield_HP = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_OHHAERK,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Ohhaerk,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Ohhaerk,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Ohhaerk,
        .shinyPalette = gMonShinyPalette_Ohhaerk,
        .iconSprite = gMonIcon_Ohhaerk,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_BOH

    //P_FAMILY_SLEEPOMPIK

    [SPECIES_SLEEPOMPIK] =
    {
        .baseHP        = 42,
        .baseAttack    = 110,
        .baseDefense   = 50,
        .baseSpAttack  = 41,
        .baseSpDefense = 40,
        .baseSpeed     = 100,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 145,
        .expYield = 112,
        
        .genderRatio = MON_MALE,
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {/*ABILITY_NARCOLEPSIE,*/ /*ABILITY_ARENA_TRAP, /*ABILITY_DEGENERATE*},
        
        .speciesName = _("Sleepompik"),
        .categoryName = _("Paralysie"),
        .height = 6,
        .weight = 70,
        //data
        .evYield_Attack = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_BLACK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_SLEEPOMPIK,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 26, SPECIES_OMINOUSLEH}),
    },

    [SPECIES_OMINOUSLEH] =
    {
        .baseHP        = 99,
        .baseAttack    = 64,
        .baseDefense   = 80,
        .baseSpAttack  = 90,
        .baseSpDefense = 67,
        .baseSpeed     = 85,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 80,
        .expYield = 180,
        
        .genderRatio = MON_MALE,
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {/*ABILITY_NARCOLEPSIE,*/ /*ABILITY_ARENA_TRAP, /*ABILITY_DEGENERATE*},
        
        .speciesName = _("Ominousleh"),
        .categoryName = _("Paralysie"),
        .height = 10,
        .weight = 500,
        //data
        .evYield_HP = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_BLACK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_OMINOUSLEH,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 48, SPECIES_MANDELMAN}),
    },

    [SPECIES_MANDELMAN] =
    {
        .baseHP        = 70,
        .baseAttack    = 110,
        .baseDefense   = 110,
        .baseSpAttack  = 100,
        .baseSpDefense = 109,
        .baseSpeed     = 45,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 35,
        .expYield = 200,
        
        .genderRatio = MON_MALE,
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {/*ABILITY_NARCOLEPSIE,*/ /*ABILITY_ARENA_TRAP, /*ABILITY_DEGENERATE*},
        
        .speciesName = _("Mandelman"),
        .categoryName = _("Paralysie"),
        .height = 19.1,
        .weight = 300,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_BLACK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_MANDELMAN,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Mandelman,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Mandelman,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Mandelman,
        .shinyPalette = gMonShinyPalette_Mandelman,
        .iconSprite = gMonIcon_Mandelman,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SLEEPOMPIK

    //P_FAMILY_CILANG

    [SPECIES_CILANG] = 
    {
        .baseHP        = 55,
        .baseAttack    = 80,
        .baseDefense   = 50,
        .baseSpAttack  = 45,
        .baseSpDefense = 50,
        .baseSpeed     = 40,
        .types = MON_TYPES(TYPE_STEEL, TYPE_ELECTRIC),

        .catchRate = 50,
        .expYield = 144,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_ANALYTIC, ABILITY_LIGHT_METAL, ABILITY_MAGNET_PULL },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Cilang"),
        .categoryName = _("Langage"),
        .height = 5,
        .weight = 100,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_ITEM, ITEM_UPGRADE, SPECIES_COMPILEX}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_CILANG,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_COMPILEX] = 
    {
        .baseHP        = 80,
        .baseAttack    = 130,
        .baseDefense   = 80,
        .baseSpAttack  = 60,
        .baseSpDefense = 70,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_STEEL, TYPE_ELECTRIC),

        .catchRate = 50,
        .expYield = 244,
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_ANALYTIC, ABILITY_LIGHT_METAL, ABILITY_MAGNET_PULL },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Compilex"),
        .categoryName = _("Optimisé"),
        .height = 10,
        .weight = 300,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_COMPILEX,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,  
    },

    //P_FAMILY_CILANG

    //P_FAMILY_RESNAKE

    [SPECIES_RESNAKE] = 
    {
        .baseHP        = 60,
        .baseAttack    = 35,
        .baseDefense   = 60,
        .baseSpAttack  = 80,
        .baseSpDefense = 60,
        .baseSpeed     = 30,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ELECTRIC),

        .catchRate = 150,
        .expYield = 80,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_DOWNLOAD, ABILITY_HEAVY_METAL, ABILITY_SIMPLE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Resnake"),
        .categoryName = _("Début Code"),
        .height = 4,
        .weight = 500,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_ITEM, ITEM_UPGRADE, SPECIES_PYTHAGON}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_RESNAKE,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    [SPECIES_PYTHAGON] = 
    {
        .baseHP        = 90,
        .baseAttack    = 60,
        .baseDefense   = 85,
        .baseSpAttack  = 120,
        .baseSpDefense = 85,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ELECTRIC),

        .catchRate = 150,
        .expYield = 80,
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_DOWNLOAD, ABILITY_HEAVY_METAL, ABILITY_SIMPLE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Pythagon"),
        .categoryName = _("Interprêté"),
        .height = 10,
        .weight = 3000,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PYTHAGON,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_RESNAKE

    //P_FAMILY_FILOURS

    [SPECIES_FILOURS] = 
    {
        .baseHP        = 44,
        .baseAttack    = 80,
        .baseDefense   = 50,
        .baseSpAttack  = 22,
        .baseSpDefense = 40,
        .baseSpeed     = 40,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_GHOST),

        .catchRate = 205,
        .expYield = 86,
        .evYield_Attack = 1,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CURSED_BODY, ABILITY_GUTS, ABILITY_NORMALIZE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Filours"),
        .categoryName = _("Ourson"),
        .height = 2,
        .weight = 20,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_POUPOURS}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FILOURS,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_POUPOURS] = 
    {
        .baseHP        = 60,
        .baseAttack    = 95,
        .baseDefense   = 72,
        .baseSpAttack  = 30,
        .baseSpDefense = 75,
        .baseSpeed     = 54,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_GHOST),

        .catchRate = 150,
        .expYield = 125,
        .evYield_Attack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CURSED_BODY, ABILITY_GUTS, ABILITY_NORMALIZE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Poupours"),
        .categoryName = _("Couture"),
        .height = 8,
        .weight = 50,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_FRIENDSHIP, 0, SPECIES_FORBEAR}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_POUPOURS,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_FORBEAR] = 
    {
        .baseHP        = 103,
        .baseAttack    = 133,
        .baseDefense   = 95,
        .baseSpAttack  = 45,
        .baseSpDefense = 60,
        .baseSpeed     = 79,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_GHOST),

        .catchRate = 90,
        .expYield = 172,
        .evYield_Attack = 1,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_CURSED_BODY, ABILITY_GUTS, ABILITY_NORMALIZE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Forbear"),
        .categoryName = _("Redemption"),
        .height = 16,
        .weight = 700,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FORBEAR,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_FILOURS

    //P_FAMILY_WIGINI

    [SPECIES_WIGINI] = 
    {
        .baseHP        = 30,
        .baseAttack    = 60,
        .baseDefense   = 60,
        .baseSpAttack  = 60,
        .baseSpDefense = 40,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_NORMAL),

        .catchRate = 205,
        .expYield = 55,
        .evYield_Defense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_TANGLING_HAIR, ABILITY_CUTE_CHARM, ABILITY_PIXILATE },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Wigini"),
        .categoryName = _("Apprenti"),
        .height = 5,
        .weight = 30,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 33, SPECIES_WIGELLE}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_WIGINI,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
    },

    [SPECIES_WIGELLE] = 
    {
        .baseHP        = 50,
        .baseAttack    = 80,
        .baseDefense   = 90,
        .baseSpAttack  = 80,
        .baseSpDefense = 60,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_NORMAL),

        .catchRate = 150,
        .expYield = 90,
        .evYield_Defense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_TANGLING_HAIR, ABILITY_CUTE_CHARM, ABILITY_PIXILATE },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Wigelle"),
        .categoryName = _("Coiffure"),
        .height = 6,
        .weight = 50,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 43, SPECIES_WIGOUDI}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_WIGELLE,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_WIGOUDI] = 
    {
        .baseHP        = 68,
        .baseAttack    = 95,
        .baseDefense   = 112,
        .baseSpAttack  = 100,
        .baseSpDefense = 65,
        .baseSpeed     = 75,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_NORMAL),

        .catchRate = 90,
        .expYield = 154,
        .evYield_Defense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_TANGLING_HAIR, ABILITY_CUTE_CHARM, ABILITY_PIXILATE },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Wigoudi"),
        .categoryName = _("Vintage"),
        .height = 10,
        .weight = 90,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_WIGOUDI,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_WIGINI

    //P_FAMILY_PUYOTAN

    [SPECIES_PUYOTAN] =
    {
        .baseHP        = 40,
        .baseAttack    = 80,
        .baseDefense   = 80,
        .baseSpAttack  = 80,
        .baseSpDefense = 80,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_DRAGON),
        .catchRate = 125,
        .expYield = 52,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_MARVEL_SCALE, ABILITY_NONE, ABILITY_MULTISCALE},
        
        .speciesName = _("Puyotan"),
        .categoryName = _("Mini Kaiju"),
        .height = 10,
        .weight = 500,
        //data
        .evYield_HP = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MONSTER),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PUYOTAN,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 53, SPECIES_PUYOMAX}),
    },

    [SPECIES_PUYOMAX] =
    {
        .baseHP        = 140,
        .baseAttack    = 110,
        .baseDefense   = 60,
        .baseSpAttack  = 110,
        .baseSpDefense = 60,
        .baseSpeed     = 45,
        .types = MON_TYPES(TYPE_DRAGON),
        .catchRate = 20,
        .expYield = 291,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_MARVEL_SCALE, ABILITY_BERSERK, ABILITY_MULTISCALE},
        
        .speciesName = _("Puyomax"),
        .categoryName = _("Kaiju"),
        .height = 70,
        .weight = 9000,
        //data
        .evYield_HP = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MONSTER),
        .bodyColor = BODY_COLOR_BLUE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PUYOMAX,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_PUYOTAN

    //P_FAMILY_POKI

    [SPECIES_POKI] = 
    {
        .baseHP        = 20,
        .baseAttack    = 76,
        .baseDefense   = 37,
        .baseSpAttack  = 50,
        .baseSpDefense = 44,
        .baseSpeed     = 72,
        .types = MON_TYPES(TYPE_DARK, TYPE_FIRE),

        .catchRate = 200,
        .expYield = 73,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_COMPETITIVE, ABILITY_ADAPTABILITY, ABILITY_CUTE_CHARM },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Poki"),
        .categoryName = _("Ptit Sourire"),
        .height = 4,
        .weight = 30,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_POKIKI}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_POKI,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset, 
        
    },

    [SPECIES_POKIKI] = 
    {
        .baseHP        = 43,
        .baseAttack    = 90,
        .baseDefense   = 50,
        .baseSpAttack  = 75,
        .baseSpDefense = 60,
        .baseSpeed     = 86,
        .types = MON_TYPES(TYPE_DARK, TYPE_FIRE),

        .catchRate = 127,
        .expYield = 122,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_COMPETITIVE, ABILITY_ADAPTABILITY, ABILITY_TINTED_LENS },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Pokiki"),
        .categoryName = _("Etudiant"),
        .height = 10,
        .weight = 150,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_POKIKIKI}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_POKIKI,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_POKIKIKI] = 
    {
        .baseHP        = 51,
        .baseAttack    = 143,
        .baseDefense   = 72,
        .baseSpAttack  = 66,
        .baseSpDefense = 83,
        .baseSpeed     = 100,
        .types = MON_TYPES(TYPE_DARK, TYPE_FIRE),

        .catchRate = 50,
        .expYield = 173,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_COMPETITIVE, ABILITY_ADAPTABILITY, ABILITY_TINTED_LENS },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Pokikiki"),
        .categoryName = _("Mageoeil"),
        .height = 14,
        .weight = 450,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_POKIKIKI,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_POKI

    //P_FAMILY_FLINGUN

    [SPECIES_FLINGUN] = 
    {
        .baseHP        = 25,
        .baseAttack    = 20,
        .baseDefense   = 30,
        .baseSpAttack  = 90,
        .baseSpDefense = 15,
        .baseSpeed     = 30,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FIGHTING),

        .catchRate = 200,
        .expYield = 64,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_BULLETPROOF, ABILITY_SNIPER, ABILITY_QUICK_DRAW },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Flingun"),
        .categoryName = _("Pistolet"),
        .height = 4,
        .weight = 50,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 27, SPECIES_KILLENCIEU}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FLINGUN,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    [SPECIES_KILLENCIEU] = 
    {
        .baseHP        = 50,
        .baseAttack    = 65,
        .baseDefense   = 60,
        .baseSpAttack  = 105,
        .baseSpDefense = 50,
        .baseSpeed     = 65,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FIGHTING),

        .catchRate = 127,
        .expYield = 120,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_BULLETPROOF, ABILITY_SNIPER, ABILITY_QUICK_DRAW },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Killencieu"),
        .categoryName = _("Double Gun"),
        .height = 10,
        .weight = 240,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 47, SPECIES_FLINKALASH}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_KILLENCIEU,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
    },

    [SPECIES_FLINKALASH] = 
    {
        .baseHP        = 63,
        .baseAttack    = 80,
        .baseDefense   = 80,
        .baseSpAttack  = 147,
        .baseSpDefense = 70,
        .baseSpeed     = 75,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FIGHTING),

        .catchRate = 50,
        .expYield = 164,
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_BULLETPROOF, ABILITY_SNIPER, ABILITY_QUICK_DRAW },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Flinkalash"),
        .categoryName = _("Kalash"),
        .height = 15,
        .weight = 470,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FLINKALASH,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
    },

    //P_FAMILY_FLINGUN

    //P_FAMILY_FINKFOK

    [SPECIES_FINKFOK] =
    {  
        .baseHP        = 70,
        .baseAttack    = 44,
        .baseDefense   = 65,
        .baseSpAttack  = 75,
        .baseSpDefense = 80,
        .baseSpeed     = 125,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_GHOST),
        .catchRate = 60,
        .expYield = 100,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {/*ABILITY_TIKTOKER,* ABILITY_EMERGENCY_EXIT},
        
        .speciesName = _("Finkfok"),
        .categoryName = _("Intangible"),
        .height = 13,
        .weight = 190,
        //data
        .evYield_Speed = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BLACK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FINKFOK,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Finkfok,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Finkfok,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Finkfok,
        .shinyPalette = gMonShinyPalette_Finkfok,
        .iconSprite = gMonIcon_Finkfok,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_FINKFOK

    //P_FAMILY_LEGZ

    [SPECIES_LEGZ] =
    {
        .baseHP        = 67,
        .baseAttack    = 80,
        .baseDefense   = 84,
        .baseSpAttack  = 80,
        .baseSpDefense = 97,
        .baseSpeed     = 97,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 60,
        .expYield = 60,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_LIMBER, ABILITY_STAMINA, ABILITY_TANGLED_FEET},
        
        .speciesName = _("Legz"),
        .categoryName = _("Jambes"),
        .height = 11,
        .weight = 500,
        //data
        .evYield_Speed = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS, EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_LEGZ,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Legz,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Legz,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Legz,
        .shinyPalette = gMonShinyPalette_Legz,
        .iconSprite = gMonIcon_Legz,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_SHINY_STONE, SPECIES_MAGNIFEET}),
    },

    [SPECIES_MAGNIFEET] =
    {
        .baseHP        = 94,
        .baseAttack    = 140,
        .baseDefense   = 100,
        .baseSpAttack  = 83,
        .baseSpDefense = 71,
        .baseSpeed     = 72,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 60,
        .expYield = 200,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_CLEAR_BODY},
        
        .speciesName = _("Magnifeet"),
        .categoryName = _("Incroyable"),
        .height = 25,
        .weight = 1600,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS, EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_MAGNIFEET,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_LEGZ

    //P_FAMILY_STOOPID

    [SPECIES_STOOPID] =
    {
        .baseHP        = 5,
        .baseAttack    = 255,
        .baseDefense   = 30,
        .baseSpAttack  = 46,
        .baseSpDefense = 200,
        .baseSpeed     = 130,
        .types = MON_TYPES(TYPE_FLYING),
        .catchRate = 60,
        .expYield = 23,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        
        .abilities = {/*ABILITY_MAIS_PUTAIN,*ABILITY_RUN_AWAY},
        
        .speciesName = _("STOOPID"),
        .categoryName = _("Fils De Pute"),
        .height = 14,
        .weight = 500,
        //data
        .evYield_HP = 3,
        .evYield_Attack = 3,
        .evYield_SpAttack = 3,
        .evYield_Defense = 3,
        .evYield_SpDefense = 3,
        .evYield_Speed = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BLACK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_STOOPID,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_STOOPID,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_STOOPID,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_STOOPID,
        .shinyPalette = gMonShinyPalette_STOOPID,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_STOOPID

    //P_FAMILY_BEUBLOP

    [SPECIES_BEUBLOP] =
    {
        .baseHP        = 90,
        .baseAttack    = 60,
        .baseDefense   = 90,
        .baseSpAttack  = 75,
        .baseSpDefense = 100,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_WATER, TYPE_FAIRY),
        .catchRate = 80,
        .expYield = 188,
        
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {/*ABILITY_IMMONDICE*ABILITY_DAMP},
        
        .speciesName = _("Beublop"),
        .categoryName = _("Blobfish"),
        .height = 9.9,
        .weight = 860,
        //data
        .evYield_SpDefense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_MONSTER),
        .bodyColor = BODY_COLOR_PINK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_BEUBLOP,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Beublop,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Beublop,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Beublop,
        .shinyPalette = gMonShinyPalette_Beublop,
        .iconSprite = gMonIcon_Beublop,
        .iconPalIndex = 2,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },
    /*
    [SPECIES_BEUBLOP_TRUE] =
    {
        .baseHP        = 90,
        .baseAttack    = 105,
        .baseDefense   = 90,
        .baseSpAttack  = 70,
        .baseSpDefense = 65,
        .baseSpeed     = 97,
        .types = MON_TYPES(TYPE_POISON, TYPE_FAIRY),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_IMMONDICE,ABILITY_INTIMIDATE},
        
        .speciesName = _("Beublop"),
        .categoryName = _("Blobfish"),
        .height = 13,
        .weight = 960,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },
    *
    //P_FAMILY_BEUBLOP

    //P_FAMILY_POTIPWET

    [SPECIES_POTIPWET] =
    {
        .baseHP        = 76,
        .baseAttack    = 34,
        .baseDefense   = 84,
        .baseSpAttack  = 56,
        .baseSpDefense = 76,
        .baseSpeed     = 12,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 190,
        .expYield = 74,
        
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_PRANKSTER, ABILITY_IMMUNITY, ABILITY_RATTLED},
        
        .speciesName = _("Potipwet"),
        .categoryName = _("Comique"),
        .height = 3.6,
        .weight = 90,
        //data
        .evYield_HP = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_POTIPWET,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Potipwet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Potipwet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Potipwet,
        .shinyPalette = gMonShinyPalette_Potipwet,
        .iconSprite = gMonIcon_Potipwet,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_FLOPWETWET}),
    },

    [SPECIES_FLOPWETWET] =
    {
        .baseHP        = 94,
        .baseAttack    = 100,
        .baseDefense   = 89,
        .baseSpAttack  = 89,
        .baseSpDefense = 77,
        .baseSpeed     = 34,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 180,
        .expYield = 150,
        
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_PRANKSTER, ABILITY_IMMUNITY, ABILITY_RATTLED},
        
        .speciesName = _("Flopwetwet"),
        .categoryName = _("Clown"),
        .height = 10,
        .weight = 560,
        //data
        .evYield_Attack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .bodyColor = BODY_COLOR_RED,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FLOPWETWET,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Flopwetwet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Flopwetwet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Flopwetwet,
        .shinyPalette = gMonShinyPalette_Flopwetwet,
        .iconSprite = gMonIcon_Flopwetwet,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_POTIPWET

    //P_FAMILY_GESTICOT

    [SPECIES_GESTICOT] =
    {
        .baseHP        = 79,
        .baseAttack    = 70,
        .baseDefense   = 68,
        .baseSpAttack  = 40,
        .baseSpDefense = 70,
        .baseSpeed     = 49,
        .types = MON_TYPES(TYPE_GROUND),
        .catchRate = 155,
        .expYield = 100,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        
        .abilities = {ABILITY_STORM_DRAIN, ABILITY_EARTH_EATER, ABILITY_HUSTLE},
        
        .speciesName = _("Gesticot"),
        .categoryName = _("Laboureur"),
        .height = 30,
        .weight = 400,
        //data
        .evYield_HP = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_GESTICOT,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Gesticot,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Gesticot,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Gesticot,
        .shinyPalette = gMonShinyPalette_Gesticot,
        .iconSprite = gMonIcon_Gesticot,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_TERRAKAMI}),
    },

    [SPECIES_TERRAKAMI] =
    {
        .baseHP        = 96,
        .baseAttack    = 110,
        .baseDefense   = 95,
        .baseSpAttack  = 66,
        .baseSpDefense = 87,
        .baseSpeed     = 85,
        .types = MON_TYPES(TYPE_GROUND, TYPE_DRAGON),
        .catchRate = 20,
        .expYield = 173,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        
        .abilities = {ABILITY_STORM_DRAIN, ABILITY_EARTH_EATER, ABILITY_SEED_SOWER},
        
        .speciesName = _("Terrakami"),
        .categoryName = _("Ver Fertile"),
        .height = 190,
        .weight = 9990,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_BROWN,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TERRAKAMI,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_GESTICOT

    //P_FAMILY_DAEMONIX

    [SPECIES_DAEMONIX] =
    {
        .baseHP        = 65,
        .baseAttack    = 80,
        .baseDefense   = 105,
        .baseSpAttack  = 75,
        .baseSpDefense = 90,
        .baseSpeed     = 85,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_DARK),
        .catchRate = 120,
        .expYield = 111,
        
        .genderRatio = PERCENT_FEMALE(95),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {/*ABILITY_VAMPIRE*ABILITY_CUTE_CHARM, ABILITY_PRANKSTER, ABILITY_MERCILESS},
        
        .speciesName = _("Daemonix"),
        .categoryName = _("Démon"),
        .height = 7,
        .weight = 200,
        //data
        .evYield_Defense = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_DAEMONIX,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Daemonix,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Daemonix,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Daemonix,
        .shinyPalette = gMonShinyPalette_Daemonix,
        .iconSprite = gMonIcon_Daemonix,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_MOON_STONE, SPECIES_ACHAETHENA}),
    },

    [SPECIES_ACHAETHENA] =
    {
        .baseHP        = 70,
        .baseAttack    = 120,
        .baseDefense   = 65,
        .baseSpAttack  = 105,
        .baseSpDefense = 30,
        .baseSpeed     = 110,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_DARK),
        .catchRate = 35,
        .expYield = 152,
        
        .genderRatio = PERCENT_FEMALE(95),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {/*ABILITY_VAMPIRE*ABILITY_CUTE_CHARM, ABILITY_MERCILESS, ABILITY_LEVITATE},
        
        .speciesName = _("Achathena"),
        .categoryName = _("Succube"),
        .height = 19.2,
        .weight = 710,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_PINK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_ACHAETHENA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Achaethena,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Achaethena,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Achaethena,
        .shinyPalette = gMonShinyPalette_Achaethena,
        .iconSprite = gMonIcon_Achaethena,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_DAEMONIX

    //P_FAMILY_PHATASM

    [SPECIES_PHANTASM] =
    {
        .baseHP        = 130,
        .baseAttack    = 89,
        .baseDefense   = 118,
        .baseSpAttack  = 69,
        .baseSpDefense = 35,
        .baseSpeed     = 58,
        .types = MON_TYPES(TYPE_GHOST, TYPE_DARK),
        .catchRate = 255,
        .expYield = 96,
        
        .genderRatio = MON_MALE,
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_STAMINA, ABILITY_INNARDS_OUT, ABILITY_LEVITATE},
        
        .speciesName = _("Phantasm"),
        .categoryName = _("Bizarre"),
        .height = 19.2,
        .weight = 1100,
        //data
        .evYield_HP = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_BLACK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_PHANTASM,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Phantasm,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Phantasm,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Phantasm,
        .shinyPalette = gMonShinyPalette_Phantasm,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SHRUMALICE

    [SPECIES_SHRUMALICE] =
    {
        .baseHP        = 95,
        .baseAttack    = 25,
        .baseDefense   = 75,
        .baseSpAttack  = 125,
        .baseSpDefense = 85,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_GRASS, TYPE_PSYCHIC),
        .catchRate = 35,
        .expYield = 138,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_INTIMIDATE, ABILITY_NONE, ABILITY_INFILTRATOR},
        
        .speciesName = _("Shroomalice"),
        .categoryName = _("Malicieux"),
        .height = 17.4,
        .weight = 1240,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .bodyColor = BODY_COLOR_PINK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_SHRUMALICE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Shroomalice,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Shroomalice,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Shroomalice,
        .shinyPalette = gMonShinyPalette_Shroomalice,
        .iconSprite = gMonIcon_Shroomalice,
        .iconPalIndex = 1,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SHRUMALICE

    //P_FAMILY_DENKID

    [SPECIES_DENKID] =
    {
        .baseHP        = 30,
        .baseAttack    = 25,
        .baseDefense   = 40,
        .baseSpAttack  = 60,
        .baseSpDefense = 40,
        .baseSpeed     = 120,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 200,
        .expYield = 63,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_STATIC, ABILITY_FLAME_BODY, ABILITY_ELECTRIC_SURGE},
        
        .speciesName = _("Denkid"),
        .categoryName = _("Elfelectrik"),
        .height = 2,
        .weight = 1,
        //data
        .evYield_Speed= 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_DENKID,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Denkid,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Denkid,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Denkid,
        .shinyPalette = gMonShinyPalette_Denkid,
        .iconSprite = gMonIcon_Denkid,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_DENKIGAN}),
    },

    [SPECIES_DENKIGAN] =
    {
        .baseHP        = 40,
        .baseAttack    = 90,
        .baseDefense   = 60,
        .baseSpAttack  = 90,
        .baseSpDefense = 65,
        .baseSpeed     = 170,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 70,
        .expYield = 53,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        
        .abilities = {ABILITY_STATIC, ABILITY_FLAME_BODY, ABILITY_ELECTRIC_SURGE},
        
        .speciesName = _("Denkigan"),
        .categoryName = _("Elfelectrik"),
        .height = 13.5,
        .weight = 1,
        //data
        .evYield_Speed = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_AMORPHOUS),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_DENKIGAN,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_DENKID

    //P_FAMILY_JAMUSH

    [SPECIES_JAMUSH] =
    {   .baseHP        = 80,
        .baseAttack    = 43,
        .baseDefense   = 81,
        .baseSpAttack  = 62,
        .baseSpDefense = 53,
        .baseSpeed     = 40,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ELECTRIC),
        .catchRate = 150,
        .expYield = 88,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_EFFECT_SPORE, ABILITY_NONE, ABILITY_VOLT_ABSORB},
        
        .speciesName = _("Jamush"),
        .categoryName = _("Champi"),
        .height = 10,
        .weight = 300,
        //data
        .evYield_HP = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_JAMUSH,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Jamush,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Jamush,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Jamush,
        .shinyPalette = gMonShinyPalette_Jamush,
        .iconSprite = gMonIcon_Jamush,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_THUNDER_STONE, SPECIES_MYCELLUM}),

    },

    [SPECIES_MYCELLUM] =
    {
        .baseHP        = 115,
        .baseAttack    = 45,
        .baseDefense   = 95,
        .baseSpAttack  = 105,
        .baseSpDefense = 93,
        .baseSpeed     = 57,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ELECTRIC),
        .catchRate = 70,
        .expYield = 147,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_EFFECT_SPORE, ABILITY_LIGHTNING_ROD, ABILITY_TRANSISTOR},
        
        .speciesName = _("Mycellum"),
        .categoryName = _("Réseau"),
        .height = 50,
        .weight = 6000,
        //data
        .evYield_HP = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_FIELD),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_MYCELLUM,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Mycellum,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Mycellum,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Mycellum,
        .shinyPalette = gMonShinyPalette_Mycellum,
        .iconSprite = gMonIcon_Mycellum,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },
    //P_FAMILY_JAMUSH
    /*
    //P_FAMILY_MEOWER

    [SPECIES_MEOWER] =
    {
        .baseHP        = 57,
        .baseAttack    = 64,
        .baseDefense   = 58,
        .baseSpAttack  = 70,
        .baseSpDefense = 52,
        .baseSpeed     = 64,
        .types = MON_TYPES(TYPE_GRASS, TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_RAIN_DISH, ABILITY_TOUGH_CLAWS, ABILITY_SUN_POWER },
        
        .speciesName = _("Meower"),
        .categoryName = _("Nenuchat"),
        .height = 5,
        .weight = 40,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_CATATION] =
    {
        .baseHP        = 80,
        .baseAttack    = 81,
        .baseDefense   = 67,
        .baseSpAttack  = 114,
        .baseSpDefense = 80,
        .baseSpeed     = 105,
        .types = MON_TYPES(TYPE_GRASS, TYPE_DARK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_RAIN_DISH, ABILITY_TOUGH_CLAWS, ABILITY_SUN_POWER },
        
        .speciesName = _("Catation"),
        .categoryName = _("Nenumatou"),
        .height = 17,
        .weight = 2100,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_MEOWER
    /*
    //P_FAMILY_PHALLION

    [SPECIES_PHALLION] =
    {
        .baseHP        = 80,
        .baseAttack    = 101,
        .baseDefense   = 95,
        .baseSpAttack  = 90,
        .baseSpDefense = 90,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_GRASS),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_SUCTION_CUPS, ABILITY_REGENERATOR, ABILITY_GOOEY},
        
        .speciesName = _("Phallion"),
        .categoryName = _("Invasif"),
        .height = 22.2,
        .weight = 1070,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_PHALLION

    //P_FAMILY_MERLADY

    [SPECIES_MERLADY] =
    {
        .baseHP        = 50,
        .baseAttack    = 30,
        .baseDefense   = 30,
        .baseSpAttack  = 65,
        .baseSpDefense = 30,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_WATER, TYPE_DARK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_SUKI_SUCTION,ABILITY_CUTE_CHARM},
        
        .speciesName = _("Merlady"),
        .categoryName = _("Sirène"),
        .height = 4.5,
        .weight = 50,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_LASSIREN] =
    {
        .baseHP        = 70,
        .baseAttack    = 70,
        .baseDefense   = 40,
        .baseSpAttack  = 80,
        .baseSpDefense = 40,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_WATER, TYPE_DARK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_SUKI_SUCTION,ABILITY_CUTE_CHARM},
        
        .speciesName = _("Lassiren"),
        .categoryName = _("Sirène"),
        .height = 10,
        .weight = 400,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_WORNYMPH] =
    {
        .baseHP        = 110,
        .baseAttack    = 110,
        .baseDefense   = 55,
        .baseSpAttack  = 110,
        .baseSpDefense = 60,
        .baseSpeed     = 105,
        .types = MON_TYPES(TYPE_WATER, TYPE_DARK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_SUKI_SUCTION,ABILITY_CUTE_CHARM},
        
        .speciesName = _("Wornymph"),
        .categoryName = _("Sirène"),
        .height = 16.7,
        .weight = 840,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_MERLADY

    //P_FAMILY_DRILLOUP

    [SPECIES_DRILLOUP] =
    {
        .baseHP        = 60,
        .baseAttack    = 70,
        .baseDefense   = 43,
        .baseSpAttack  = 20,
        .baseSpDefense = 11,
        .baseSpeed     = 49,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_STURDY, ABILITY_SCREEN_CLEANER, ABILITY_STEELWORKER},
        
        .speciesName = _("Drilloup"),
        .categoryName = _("Perceur"),
        .height = 5.6,
        .weight = 300,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_PERCYBORG] =
    {
        .baseHP        = 72,
        .baseAttack    = 122,
        .baseDefense   = 111,
        .baseSpAttack  = 84,
        .baseSpDefense = 66,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_STEEL, TYPE_FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_STURDY, ABILITY_SCREEN_CLEANER, ABILITY_STEELWORKER},
        
        .speciesName = _("Percyborg"),
        .categoryName = _("Foreur"),
        .height = 13.5,
        .weight = 670,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_PERCYBORG
    *
    //P_FAMILY_WICHU

    [SPECIES_WICHU] =
    {
        .baseHP        = 140,
        .baseAttack    = 10,
        .baseDefense   = 55,
        .baseSpAttack  = 65,
        .baseSpDefense = 95,
        .baseSpeed     = 120,
        .types = MON_TYPES(TYPE_FAIRY),
        .catchRate = 100,
        .expYield = 300,
        
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_SERENE_GRACE, ABILITY_SUPER_LUCK, ABILITY_SYNCHRONIZE},
        
        .speciesName = _("Wichu"),
        .categoryName = _("Comète"),
        .height = 4,
        .weight = 800,
        //data
        .evYield_HP = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .bodyColor = BODY_COLOR_YELLOW,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_WICHU,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_WICHU
    /*
    //P_FAMILY_INCARNAPOT

    [SPECIES_INCARNAPOT] =
    {
        .baseHP        = 60,
        .baseAttack    = 40,
        .baseDefense   = 60,
        .baseSpAttack  = 45,
        .baseSpDefense = 60,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_MAGIC_BOUNCE, ABILITY_TRACE, ABILITY_PSYCHIC_SURGE},
        
        .speciesName = _("Incarnapot"),
        .categoryName = _("Vase"),
        .height = 6,
        .weight = 150,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_VASAGE] =
    {
        .baseHP        = 90,
        .baseAttack    = 80,
        .baseDefense   = 100,
        .baseSpAttack  = 84,
        .baseSpDefense = 110,
        .baseSpeed     = 43,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_MAGIC_BOUNCE, ABILITY_TRACE, ABILITY_PSYCHIC_SURGE},
        
        .speciesName = _("Vasage"),
        .categoryName = _("Incarnation"),
        .height = 9,
        .weight = 400,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_POTERNE]  
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_INCARNAPOT
    *
    //P_FAMILY_FIGGON

    [SPECIES_FIGGON] =
    {
        .baseHP        = 33,
        .baseAttack    = 40,
        .baseDefense   = 25,
        .baseSpAttack  = 15,
        .baseSpDefense = 42,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 255,
        .expYield = 59,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_STRONG_JAW, ABILITY_LEAF_GUARD, ABILITY_HARVEST},
        
        .speciesName = _("Figgon"),
        .categoryName = _("Plantoeuf"),
        .height = 1,
        .weight = 5,
        //data
        .evYield_Speed = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_FIGGON,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_SALADRAKE}),
    },

    [SPECIES_SALADRAKE] =
    {
        .baseHP        = 50,
        .baseAttack    = 80,
        .baseDefense   = 80,
        .baseSpAttack  = 20,
        .baseSpDefense = 80,
        .baseSpeed     = 42,
        .types = MON_TYPES(TYPE_GRASS, TYPE_DRAGON),
        .catchRate = 125,
        .expYield = 111,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_STRONG_JAW, ABILITY_LEAF_GUARD, ABILITY_HARVEST},
        
        .speciesName = _("Saladrake"),
        .categoryName = _("Aubergine"),
        .height = 8.4,
        .weight = 570,
        //data
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_DRAGON),
        .bodyColor = BODY_COLOR_PINK,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_SALADRAKE,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_AUBERJAW}),
    },

    [SPECIES_AUBERJAW] =
    {
        .baseHP        = 100,
        .baseAttack    = 95,
        .baseDefense   = 130,
        .baseSpAttack  = 65,
        .baseSpDefense = 60,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_GRASS, TYPE_DRAGON),
        .catchRate = 45,
        .expYield = 188,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_STRONG_JAW, ABILITY_LEAF_GUARD, ABILITY_HARVEST},
        
        .speciesName = _("Auberjaw"),
        .categoryName = _("Grobergine"),
        .height = 20,
        .weight = 1000,
        //data
        .evYield_Attack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_DRAGON),
        .bodyColor = BODY_COLOR_PURPLE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_AUBERJAW,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SALADRAKE
    /*
    //P_FAMILY_FOURUGLA

    [SPECIES_FOURUGLA] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_YETIDIOT] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_FOURUGLA

    //P_FAMILY_PRISMITI

    [SPECIES_PRISMITI] =
    {
        .baseHP        = 20,
        .baseAttack    = 33,
        .baseDefense   = 43,
        .baseSpAttack  = 40,
        .baseSpDefense = 55,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_ROCK, TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_FOREWARN, ABILITY_LEVITATE, ABILITY_MAGIC_GUARD},
        
        .speciesName = _("Emprism"),
        .categoryName = _("Prisme"),
        .height = 1.1,
        .weight = 1000,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_PRISMUNTER] =
    {
        .baseHP        = 65,
        .baseAttack    = 82,
        .baseDefense   = 100,
        .baseSpAttack  = 105,
        .baseSpDefense = 50,
        .baseSpeed     = 141,
        .types = MON_TYPES(TYPE_ROCK, TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_FOREWARN, ABILITY_PRISM_ARMOR, ABILITY_MAGIC_GUARD},
        
        .speciesName = _("Prsimunter"),
        .categoryName = _("Chasseur"),
        .height = 21.6,
        .weight = 1350,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_PRISMITI anciennement Gemo et Galaxithe rip

    //P_FAMILY_OCTONIMBUS

    [SPECIES_OCTONIMBUS] =
    {
        .baseHP        = 30,
        .baseAttack    = 36,
        .baseDefense   = 27,
        .baseSpAttack  = 70,
        .baseSpDefense = 60,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_GHOST, TYPE_FLYING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_CLOUD_NINE},
        
        .speciesName = _("Octonimbus"),
        .categoryName = _("Poulpociel"),
        .height = 8,
        .weight = 10,
    },

    [SPECIES_ATMOCTOPUS] =
    {
        .baseHP        = 80,
        .baseAttack    = 52,
        .baseDefense   = 46,
        .baseSpAttack  = 103,
        .baseSpDefense = 98,
        .baseSpeed     = 76,
        .types = MON_TYPES(TYPE_GHOST, TYPE_FLYING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_DRIZZLE, ABILITY_SNOW_WARNING, ABILITY_CLOUD_NINE},
        
        .speciesName = _("Atmoctopus"),
        .categoryName = _("Météo Poulpe"),
        .height = 400,
        .weight = 50,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_OCTONIMBUS

    //P_FAMILY_LIMACIDE

    [SPECIES_LIMACIDE] =
    {
        .baseHP        = 50,
        .baseAttack    = 27,
        .baseDefense   = 43,
        .baseSpAttack  = 80,
        .baseSpDefense = 50,
        .baseSpeed     = 32,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_POISON_POINT, ABILITY_GOOEY, ABILITY_POISON_HEAL},
        
        .speciesName = _("Limacide"),
        .categoryName = _("Limace"),
        .height = 3,
        .weight = 20,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_GLAUGOON] =
    {
        .baseHP        = 85,
        .baseAttack    = 72,
        .baseDefense   = 85,
        .baseSpAttack  = 125,
        .baseSpDefense = 76,
        .baseSpeed     = 83,
        .types = MON_TYPES(TYPE_WATER, TYPE_DRAGON),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_POISON_POINT, ABILITY_GOOEY, ABILITY_POISON_HEAL},
        
        .speciesName = _("Glaugoon"),
        .categoryName = _("Ange de Mer"),
        .height = 10,
        .weight = 70,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_LIMACIDE

    //P_FAMILY_PHLOTOXICO

    [SPECIES_PHLOTOXICO] =
    {
        .baseHP        = 100,
        .baseAttack    = 37,
        .baseDefense   = 81,
        .baseSpAttack  = 92,
        .baseSpDefense = 99,
        .baseSpeed     = 5,
        .types = MON_TYPES(TYPE_POISON, TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_POISON_POINT, ABILITY_WATER_BUBBLE},
        
        .speciesName = _("Phlotoxico"),
        .categoryName = _("Physalie"),
        .height = 9,
        .weight = 50,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_PHLOTOXICO

    //P_FAMILY_WUFUR

    [SPECIES_WUFUR] =
    {
        .baseHP        = 50,
        .baseAttack    = 62,
        .baseDefense   = 50,
        .baseSpAttack  = 40,
        .baseSpDefense = 50,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_KEEN_EYE, ABILITY_RIVALRY, ABILITY_HUSTLE},
        
        .speciesName = _("Wufur"),
        .categoryName = _("Compagnon"),
        .height = 5,
        .weight = 90,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_NUNCHAKOS] =
    {
        .baseHP        = 82,
        .baseAttack    = 85,
        .baseDefense   = 80,
        .baseSpAttack  = 69,
        .baseSpDefense = 71,
        .baseSpeed     = 94,
        .types = MON_TYPES(TYPE_DARK, TYPE_FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_KEEN_EYE, ABILITY_RIVALRY, ABILITY_HUSTLE},
        
        .speciesName = _("Nunchakos"),
        .categoryName = _("Loup Marcial"),
        .height = 15,
        .weight = 720,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_WUFUR

    //P_FAMILY_CAESABLESS

    [SPECIES_CAESABLESS] =
    {
        .baseHP        = 126,
        .baseAttack    = 69,
        .baseDefense   = 69,
        .baseSpAttack  = 80,
        .baseSpDefense = 116,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_WATER, TYPE_FAIRY),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_HYDRATION, ABILITY_CLEAR_BODY},
        
        .speciesName = _("Caesabless"),
        .categoryName = _("Great Fairy"),
        .height = 16,
        .weight = 800,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_CAESABLESS

    //P_FAMILY_HAPIDUSE

    [SPECIES_HAPIDUSE] =
    {
        .baseHP        = 80,
        .baseAttack    = 30,
        .baseDefense   = 30,
        .baseSpAttack  = 30,
        .baseSpDefense = 30,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_CUTE_CHARM, ABILITY_STATIC, ABILITY_WATER_VEIL},
        
        .speciesName = _("Hapiduse"),
        .categoryName = _("Polype"),
        .height = 1,
        .weight = 1,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_PERDUSE] =
    {
        .baseHP        = 98,
        .baseAttack    = 80,
        .baseDefense   = 70,
        .baseSpAttack  = 71,
        .baseSpDefense = 88,
        .baseSpeed     = 46,
        .types = MON_TYPES(TYPE_POISON, TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_CUTE_CHARM, ABILITY_STATIC, ABILITY_WATER_VEIL},
        
        .speciesName = _("Perduse"),
        .categoryName = _("Méduse"),
        .height = 9,
        .weight = 150,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_MEDERIVE] =
    {
        .baseHP        = 119,
        .baseAttack    = 80,
        .baseDefense   = 80,
        .baseSpAttack  = 90,
        .baseSpDefense = 10,
        .baseSpeed     = 81,
        .types = MON_TYPES(TYPE_POISON, TYPE_GHOST),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_CUTE_CHARM, ABILITY_STATIC, ABILITY_WATER_VEIL},
        
        .speciesName = _("Medérive"),
        .categoryName = _("Méduse Voile"),
        .height = 150,
        .weight = 1340,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_HAPIDUSE

    //P_FAMILY_ILLUFOX

    [SPECIES_ILLUFOX] =
    {
        .baseHP        = 55,
        .baseAttack    = 79,
        .baseDefense   = 25,
        .baseSpAttack  = 79,
        .baseSpDefense = 25,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_MAGIC_BOUNCE},
        
        .speciesName = _("Illufox"),
        .categoryName = _("RenardEtoile"),
        .height = 10,
        .weight = 300,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_SPERENARD] =
    {
        .baseHP        = 73,
        .baseAttack    = 100,
        .baseDefense   = 55,
        .baseSpAttack  = 100,
        .baseSpDefense = 55,
        .baseSpeed     = 113,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_MAGIC_BOUNCE},
        
        .speciesName = _("Sperenard"),
        .categoryName = _("RenardEtoile"),
        .height = 17,
        .weight = 910,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_ILLUFOX

    //P_FAMILY_MOUCHIPS

    [SPECIES_MOUCHIPS] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_GIGANILLE] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_PROBELLE] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = MON_FEMALE,
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_MOUCHIPS

    //P_FAMILY_POME

    [SPECIES_POME] =
    {
        .baseHP        = 40,
        .baseAttack    = 40,
        .baseDefense   = 40,
        .baseSpAttack  = 40,
        .baseSpDefense = 40,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_FURTIF,  ABILITY_INNER_FOCUS, ABILITY_GALE_WINGS},
        
        .speciesName = _("Pome"),
        .categoryName = _("Hou Hou"),
        .height = 1,
        .weight = 1,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_POMDARPI] =
    {
        .baseHP        = 65,
        .baseAttack    = 110,
        .baseDefense   = 65,
        .baseSpAttack  = 110,
        .baseSpDefense = 65,
        .baseSpeed     = 120,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_FURTIF,  ABILITY_INNER_FOCUS, ABILITY_GALE_WINGS},
        
        .speciesName = _("Pomdarpi"),
        .categoryName = _("Immitation"),
        .height = 30,
        .weight = 1560,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_POME

    //P_FAMILY_KEROCORN

    [SPECIES_KEROCORN] =
    {
        .baseHP        = 45,
        .baseAttack    = 20,
        .baseDefense   = 30,
        .baseSpAttack  = 45,
        .baseSpDefense = 40,
        .baseSpeed     = 63,
        .types = MON_TYPES(TYPE_GRASS, TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_LEAF_GUARD, ABILITY_CHEEK_POUCH, ABILITY_DRIZZLE},
        
        .speciesName = _("Kercorn"),
        .categoryName = _("Glannouille"),
        .height = 2,
        .weight = 2.5,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_CROACORN] =
    {
        .baseHP        = 51,
        .baseAttack    = 35,
        .baseDefense   = 55,
        .baseSpAttack  = 60,
        .baseSpDefense = 70,
        .baseSpeed     = 70,
        .types = MON_TYPES(TYPE_GRASS, TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_LEAF_GUARD, ABILITY_CHEEK_POUCH, ABILITY_DRIZZLE},
        
        .speciesName = _("Croacorn"),
        .categoryName = _("Glannouille"),
        .height = 7.5,
        .weight = 80,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_CROAQUILLE] =
    {
        .baseHP        = 80,
        .baseAttack    = 70,
        .baseDefense   = 90,
        .baseSpAttack  = 85,
        .baseSpDefense = 95,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_GRASS, TYPE_WATER),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_LEAF_GUARD, ABILITY_CHEEK_POUCH, ABILITY_DRIZZLE},
        
        .speciesName = _("Croaquille"),
        .categoryName = _("Glannouille"),
        .height = 20,
        .weight = 2500,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_KEROCORN

    //P_FAMILY_CHIMESPRIT

    [SPECIES_CHIMESPIT] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_CHIMESPRIT

    //P_FAMILY_INDORMON

    [SPECIES_INDORMON] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_INVOCAMON] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_INDORMON

    //P_FAMILY_MINUISIBLE

    [SPECIES_MINUISIBLE] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    [SPECIES_MINOCIVE] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_MINUISIBLE

    //P_FAMILY_SHERURAN

    [SPECIES_SHERURAN] =
    {
        .baseHP        = 68,
        .baseAttack    = 51,
        .baseDefense   = 76,
        .baseSpAttack  = 45,
        .baseSpDefense = 30,
        .baseSpeed     = 41,
        .types = MON_TYPES(TYPE_STEEL, TYPE_POISON),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_POISON_POINT, ABILITY_AFTERMATH, ABILITY_CORROSION},
        
        .speciesName = _("Sheruran"),
        .categoryName = _("Nucléaire"),
        .height = 3.3,
        .weight = 20,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_SHERUNIUM] =
    {
        .baseHP        = 80,
        .baseAttack    = 130,
        .baseDefense   = 110,
        .baseSpAttack  = 95,
        .baseSpDefense = 95,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_STEEL, TYPE_POISON),  
        .catchRate = , 
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_POISON_POINT, ABILITY_AFTERMATH, ABILITY_CORROSION},
        
        .speciesName = _("Sherunium"),
        .categoryName = _("Nucléaire"),
        .height = 15,
        .weight = 1800,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    [SPECIES_SHERUCROC] =
    {
        .baseHP        = 55,
        .baseAttack    = 105,
        .baseDefense   = 85,
        .baseSpAttack  = 115,
        .baseSpDefense = 70,
        .baseSpeed     = 100,
        .types = MON_TYPES(TYPE_STEEL, TYPE_POISON),  
        .catchRate = , 
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_POISON_POINT, ABILITY_AFTERMATH, ABILITY_CORROSION},
        
        .speciesName = _("Sherucroc"),
        .categoryName = _("Nucléaire"),
        .height = 15,
        .weight = 1800,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_SHERURAN

    //P_FAMILY_GOTINALVE

    [SPECIES_GOTINALVE] =
    {
        .baseHP        = 140,
        .baseAttack    = 70,
        .baseDefense   = 60,
        .baseSpAttack  = 60,
        .baseSpDefense = 70,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_GHOST, TYPE_NORMAL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_HOSPITALITY, ABILITY_HEALING_SHIFT},
        
        .speciesName = _("Gotinalve"),
        .categoryName = _("Soigneur"),
        .height = 4,
        .weight = 20,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_GOTINALVE

    //P_FAMILY_SYNAPTI

    [SPECIES_SYNAPTI] =
    {
        .baseHP        = 42,
        .baseAttack    = 5,
        .baseDefense   = 10,
        .baseSpAttack  = 110,
        .baseSpDefense = 80,
        .baseSpeed     = 48,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_COMPETITIVE, ABILITY_NONE, ABILITY_ANALYTIC},
        
        .speciesName = _("Synapti"),
        .categoryName = _("Nerveux"),
        .height = 18,
        .weight = 150,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_GLACYNAPSE] =
    {
        .baseHP        = 75,
        .baseAttack    = 110,
        .baseDefense   = 48,
        .baseSpAttack  = 60,
        .baseSpDefense = 67,
        .baseSpeed     = 110,
        .types = MON_TYPES(TYPE_ICE, TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_RECKLESS, ABILITY_ICE_BODY, ABILITY_ANALYTIC},
        
        .speciesName = _("Glacynapse"),
        .categoryName = _("Cérébral"),
        .height = 18,
        .weight = 900,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_SYNAPTI

    //P_FAMILY_BEBETA

    [SPECIES_BEBETA] =
    {
        .baseHP        = 80,
        .baseAttack    = 70,
        .baseDefense   = 50,
        .baseSpAttack  = 80,
        .baseSpDefense = 61,
        .baseSpeed     = 20,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_DARK),
        .catchRate = 200,
        .expYield = 83,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_MAGNET_PULL, ABILITY_DOWNLOAD, ABILITY_VOLT_ABSORB},
        
        .speciesName = _("Bebeta"),
        .categoryName = _("Dump Media"),
        .height = 10,
        .weight = 200,
        //data
        .evYield_SpAttack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS, EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_BEBETA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 44, SPECIES_OMEGAMMA}),
    },

    [SPECIES_OMEGAMMA] =
    {
        .baseHP        = 104,
        .baseAttack    = 95,
        .baseDefense   = 70,
        .baseSpAttack  = 109,
        .baseSpDefense = 82,
        .baseSpeed     = 55,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_DARK),
        .catchRate = 30,
        .expYield = 199,
        
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        
        .abilities = {ABILITY_MAGNET_PULL, ABILITY_DOWNLOAD, ABILITY_VOLT_ABSORB},
        
        .speciesName = _("Omegamma"),
        .categoryName = _("Lost Media"),
        .height = 20,
        .weight = 4000,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS, EGG_GROUP_MINERAL),
        .bodyColor = BODY_COLOR_GRAY,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_OMEGAMMA,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_BEBETA

    //P_FAMILY_TERMALIN

    [SPECIES_TERMALIN] =
    {
        .baseHP        = 50,
        .baseAttack    = 45,
        .baseDefense   = 55,
        .baseSpAttack  = 70,
        .baseSpDefense = 55,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 170,
        .expYield = 99,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_WHITE_SMOKE, ABILITY_FLAME_BODY, ABILITY_RIVALRY},
        
        .speciesName = _("Termalin"),
        .categoryName = _("BainMacaque"),
        .height = 10,
        .weight = 150,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TERMALIN,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL_MALE, 46, SPECIES_TERMITORIAL},
                                {EVO_LEVEL_FEMALE, 46, SPECIES_TERBABAIN}),
    },

    [SPECIES_TERMITORIAL] =
    {
        .baseHP        = 105,
        .baseAttack    = 96,
        .baseDefense   = 61,
        .baseSpAttack  = 134,
        .baseSpDefense = 45,
        .baseSpeed     = 54,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 50,
        .expYield = 175,
        
        .genderRatio = MON_MALE,
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_WHITE_SMOKE, ABILITY_FLAME_BODY, ABILITY_RIVALRY},
        
        .speciesName = _("Termitorial"),
        .categoryName = _("BainMacaque"),
        .height = 20,
        .weight = 1200,
        //data
        .evYield_SpAttack = 3,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TERMITORIAL,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    [SPECIES_TERBABAIN] =
    {
        .baseHP        = 105,
        .baseAttack    = 96,
        .baseDefense   = 61,
        .baseSpAttack  = 134,
        .baseSpDefense = 45,
        .baseSpeed     = 54,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 100,
        .expYield = 202,
        
        .genderRatio = MON_FEMALE,
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        
        .abilities = {ABILITY_WHITE_SMOKE, ABILITY_FLAME_BODY, ABILITY_PARENTAL_BOND},
        
        .speciesName = _("Terbabain"),
        .categoryName = _("BainMacaque"),
        .height = 13,
        .weight = 600,
        //data
        .evYield_Attack = 2,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_HUMAN_LIKE),
        .bodyColor = BODY_COLOR_WHITE,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_TERBABAIN,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_TERMALIN

    //P_FAMILY_GLAKAME

    [SPECIES_GLAKAME] =
    {
        .baseHP        = 40,
        .baseAttack    = 50,
        .baseDefense   = 110,
        .baseSpAttack  = 50,
        .baseSpDefense = 80,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_ICE, TYPE_STEEL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_ICE_BODY, ABILITY_CONTRARY, ABILITY_ICE_SCALES},
        
        .speciesName = _("Glakame"),
        .categoryName = _("Tortue Glace"),
        .height = 10,
        .weight = 1000,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_KAMEPHALE] =
    {
        .baseHP        = 60,
        .baseAttack    = 70,
        .baseDefense   = 200,
        .baseSpAttack  = 70,
        .baseSpDefense = 80,
        .baseSpeed     = 10,
        .types = MON_TYPES(TYPE_ICE, TYPE_STEEL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_ICE_BODY, ABILITY_CONTRARY, ABILITY_ICE_SCALES},
        
        .speciesName = _("Kamephale"),
        .categoryName = _("Bycéphale"),
        .height = 14,
        .weight = 4000,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_GLAKAME

    //P_FAMILY_MOUMOUTROP

    [SPECIES_MOUMOUTROP] =
    {
        .baseHP        = 60,
        .baseAttack    = 60,
        .baseDefense   = 80,
        .baseSpAttack  = 60,
        .baseSpDefense = 30,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_ICE, TYPE_DRAGON),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_BULLETPROOF, ABILITY_FUR_COAT, ABILITY_SKILL_LINK},
        
        .speciesName = _("Moumoutrop"),
        .categoryName = _("Moumoute"),
        .height = 7.5,
        .weight = 200,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_TUNDRAGON] =
    {
        .baseHP        = 60,
        .baseAttack    = 95,
        .baseDefense   = 130,
        .baseSpAttack  = 95,
        .baseSpDefense = 40,
        .baseSpeed     = 105,
        .types = MON_TYPES(TYPE_ICE, TYPE_DRAGON),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_BULLETPROOF, ABILITY_FUR_COAT, ABILITY_SKILL_LINK},
        
        .speciesName = _("Tundragon"),
        .categoryName = _("Dragon Laine"),
        .height = 12,
        .weight = 600,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_MOUMOUTROP

    //P_FAMILY_BLASTAILES

    [SPECIES_BLASTAILES] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_BLASTAILES

    //P_FAMILY_BEAUVY

    [SPECIES_BEAUVY] =
    {
        .baseHP        = 30,
        .baseAttack    = 100,
        .baseDefense   = 60,
        .baseSpAttack  = 50,
        .baseSpDefense = 60,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_OBLIVIOUS, ABILITY_NONE, ABILITY_RECKLESS},
        
        .speciesName = _("Beauvy"),
        .categoryName = _("Veau"),
        .height = 7.8,
        .weight = 80,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_ROSTIER] =
    {
        .baseHP        = 44,
        .baseAttack    = 140,
        .baseDefense   = 95,
        .baseSpAttack  = 40,
        .baseSpDefense = 85,
        .baseSpeed     = 85,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = /*{ABILITY_TAURINE, ABILITY_NONE, ABILITY_RECKLESS},
        
        .speciesName = _("Rostier"),
        .categoryName = _("Taurine"),
        .height = 14,
        .weight = 430,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_BEAUVY

    //P_FAMILY_METALICA

    [SPECIES_METALICA] =
    {
        .baseHP        = 55,
        .baseAttack    = 112,
        .baseDefense   = 130,
        .baseSpAttack  = 60,
        .baseSpDefense = 90,
        .baseSpeed     = 40,
        .types = MON_TYPES(TYPE_STEEL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_IRON_FIST, ABILITY_HEATPROOF, ABILITY_HEAVY_METAL},
        
        .speciesName = _("Metalica"),
        .categoryName = _("Discipline"),
        .height = 16,
        .weight = 3000,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_METALICA

    //P_FAMILY_POPCORNE

    [SPECIES_POPCORNE] =
    {
        .baseHP        = 20,
        .baseAttack    = 30,
        .baseDefense   = 10,
        .baseSpAttack  = 20,
        .baseSpDefense = 20,
        .baseSpeed     = 100,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_LEVITATE, ABILITY_NONE, ABILITY_CHILLING_NEIGH},
        
        .speciesName = _("Popcorne"),
        .categoryName = _("Poulin"),
        .height = 2,
        .weight = 110,//data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_EQUESTRIA] =
    {
        .baseHP        = 60,
        .baseAttack    = 50,
        .baseDefense   = 60,
        .baseSpAttack  = 88,
        .baseSpDefense = 48,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_FLYING, TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_GALLOPAGE, ABILITY_SYNCHRONIZE, ABILITY_CHILLING_NEIGH},
        
        .speciesName = _("Equestria"),
        .categoryName = _("Etalon"),
        .height = 15,
        .weight = 1000,//data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_PEGAZUR] =
    {
        .baseHP        = 70,
        .baseAttack    = 100,
        .baseDefense   = 80,
        .baseSpAttack  = 70,
        .baseSpDefense = 60,
        .baseSpeed     = 130,
        .types = MON_TYPES(TYPE_FLYING, TYPE_PSYCHIC),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_GALLOPAGE, ABILITY_SYNCHRONIZE, ABILITY_CHILLING_NEIGH},
        
        .speciesName = _("Pégazur"),
        .categoryName = _("Pégase"),
        .height = 22,
        .weight = 3000,//data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_POPCORNE

    //P_FAMILY_PUTRAVEN

    [SPECIES_PUTRAVEN] =
    {
        .baseHP        = 40,
        .baseAttack    = 70,
        .baseDefense   = 40,
        .baseSpAttack  = 65,
        .baseSpDefense = 30,
        .baseSpeed     = 100,
        .types = MON_TYPES(TYPE_ROCK, TYPE_GROUND),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_SOLID_ROCK, ABILITY_TELEPATHY},
        
        .speciesName = _("Putraven"),
        .categoryName = _("Chatiment"),
        .height = 2.4,
        .weight = 9,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_NECROVORIS] =
    {
        .baseHP        = 70,
        .baseAttack    = 50,
        .baseDefense   = 120,
        .baseSpAttack  = 45,
        .baseSpDefense = 130,
        .baseSpeed     = 20,
        .types = MON_TYPES(TYPE_ROCK, TYPE_GROUND),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_SOLID_ROCK, ABILITY_TELEPATHY},
        
        .speciesName = _("Necrovoris"),
        .categoryName = _("Putrefaction"),
        .height = 17.3,
        .weight = 1320,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_KIDOCATE

    //P_FAMILY_ROCHIERE

    [SPECIES_ROCHIERE] = 
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_ROCHIERE

    //P_FAMILY_OSTENSSY

    [SPECIES_OSTENSSY] =
    {
        .baseHP        = 35,
        .baseAttack    = 50,
        .baseDefense   = 71,
        .baseSpAttack  = 40,
        .baseSpDefense = 40,
        .baseSpeed     = 5,
        .types = MON_TYPES(TYPE_GHOST, TYPE_ROCK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_FRAGMENTATION, ABILITY_CURSED_BODY, ABILITY_STURDY},
        
        .speciesName = _("Ostenssy"),
        .categoryName = _("Crâne"),
        .height = 5.7,
        .weight = 740,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_RANCOSSOR] =
    {
        .baseHP        = 100,
        .baseAttack    = 143,
        .baseDefense   = 70,
        .baseSpAttack  = 61,
        .baseSpDefense = 76,
        .baseSpeed     = 85,
        .types = MON_TYPES(TYPE_GHOST, TYPE_ROCK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_FRAGMENTATION, ABILITY_CURSED_BODY, ABILITY_ROCK_HEAD},
        
        .speciesName = _("Rancossor"),
        .categoryName = _("Rancoeur"),
        .height = 12.1,
        .weight = 1270,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_MOSSEMEROS] =
    {
        .baseHP        = 81,
        .baseAttack    = 57,
        .baseDefense   = 80,
        .baseSpAttack  = 122,
        .baseSpDefense = 135,
        .baseSpeed     = 60,
        .types = MON_TYPES(TYPE_GHOST, TYPE_ROCK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {/*ABILITY_FRAGMENTATION, ABILITY_CURSED_BODY, ABILITY_SOLID_ROCK},
        
        .speciesName = _("Mossemeros"),
        .categoryName = _("Déchu"),
        .height = 13.1,
        .weight = 2310,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_OSTENSSY

    //P_FAMILY_JAIMAILLE

    [SPECIES_JAIMAILLE] =
    {
        .baseHP        = 50,
        .baseAttack    = 40,
        .baseDefense   = 60,
        .baseSpAttack  = 40,
        .baseSpDefense = 60,
        .baseSpeed     = 120,
        .types = MON_TYPES(TYPE_STEEL, TYPE_GHOST),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_LONG_REACH, ABILITY_BATTLE_ARMOR, ABILITY_SHARPNESS},
        
        .speciesName = _("Jaimaille"),
        .categoryName = _("Errant"),
        .height = 3,
        .weight = 20,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_ARMIS] =
    {
        .baseHP        = 50,
        .baseAttack    = 60,
        .baseDefense   = 100,
        .baseSpAttack  = 60,
        .baseSpDefense = 100,
        .baseSpeed     = 80,
        .types = MON_TYPES(TYPE_STEEL, TYPE_GHOST),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_LONG_REACH, ABILITY_BATTLE_ARMOR, ABILITY_SHARPNESS},
        
        .speciesName = _("Armis"),
        .categoryName = _("Errant"),
        .height = 11,
        .weight = 80,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_ACCALMITE] =
    {
        .baseHP        = 50,
        .baseAttack    = 110,
        .baseDefense   = 120,
        .baseSpAttack  = 115,
        .baseSpDefense = 100,
        .baseSpeed     = 65,
        .types = MON_TYPES(TYPE_STEEL, TYPE_GHOST),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_LONG_REACH, ABILITY_BATTLE_ARMOR, ABILITY_SHARPNESS},
        
        .speciesName = _("Accalmité"),
        .categoryName = _("Apogée"),
        .height = 19,
        .weight = 200,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_JAIMAILLE

    //P_FAMILY_TROMPLANTE

    [SPECIES_TROMPLANTE] =
    {
        .baseHP        = 40,
        .baseAttack    = 90,
        .baseDefense   = 70,
        .baseSpAttack  = 50,
        .baseSpDefense = 80,
        .baseSpeed     = 45,
        .types = MON_TYPES(TYPE_POISON, TYPE_FAIRY),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_SUPERSWEET_SYRUP, ABILITY_ILLUMINATE, ABILITY_STICKY_HOLD},
        
        .speciesName = _("Tromplante"),
        .categoryName = _("Piégeur"),
        .height = 6,
        .weight = 300,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_PADAMIDON] =
    {
        .baseHP        = 65,
        .baseAttack    = 120,
        .baseDefense   = 80,
        .baseSpAttack  = 90,
        .baseSpDefense = 100,
        .baseSpeed     = 15,
        .types = MON_TYPES(TYPE_POISON, TYPE_FAIRY),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_SUPERSWEET_SYRUP, ABILITY_ILLUMINATE, ABILITY_STICKY_HOLD},
        
        .speciesName = _("Padamidon"),
        .categoryName = _("Trompeur"),
        .height = 13,
        .weight = 2000,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_TROMPLANTE

    //P_FAMILY_PSYCHOBAT

    [SPECIES_PSYCHOBAT] =
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _("Psychobat"),
        .categoryName = _("Psychotoxic"),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 46, SPECIES_}),
    },

    [SPECIES_CHIROPSY] =
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _("Chiropsy"),
        .categoryName = _("Psychotoxic"),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
    },

    //P_FAMILY_PSYCHOBAT

    //P_FAMILY_SABSUTE

    [SPECIES_GYAOON] =
    {
        .baseHP        = 100,
        .baseAttack    = 65,
        .baseDefense   = 110,
        .baseSpAttack  = 65,
        .baseSpDefense = 100,
        .baseSpeed     = 50,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_CUTE_CHARM, ABILITY_FLUFFY, ABILITY_FRIEND_GUARD},
        
        .speciesName = _("Gyaoon"),
        .categoryName = _("Référence"),
        .height = 4,
        .weight = 12,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_SABSUTE

    //P_FAMILY_COUVETEAU

    [SPECIES_COUVETEAU] =
    {
        .baseHP        = 46,
        .baseAttack    = 79,
        .baseDefense   = 52,
        .baseSpAttack  = 44,
        .baseSpDefense = 92,
        .baseSpeed     = 34,
        .types = MON_TYPES(TYPE_ROCK, TYPE_ICE), 
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_OVERCOAT, ABILITY_SLUSH_RUSH, /*ABILITY_FURTIF},
        
        .speciesName = _("Couveteau"),
        .categoryName = _("Fourrure"),
        .height = 3.2,
        .weight = 30,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_LOUVERNAL] =
    {
        .baseHP        = 62,
        .baseAttack    = 115,
        .baseDefense   = 71,
        .baseSpAttack  = 80,
        .baseSpDefense = 112,
        .baseSpeed     = 75,
        .types = MON_TYPES(TYPE_ROCK, TYPE_ICE),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_OVERCOAT, ABILITY_SLUSH_RUSH, /*ABILITY_FURTIF},
        
        .speciesName = _("Louvernal"),
        .categoryName = _("Loup Glacial"),
        .height = 14.4,
        .weight = 400,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_COUVETEAU

    //P_FAMILY_LARVAMBRE

    [SPECIES_LARVAMBRE] =
    {
        .baseHP        = 30,
        .baseAttack    = 40,
        .baseDefense   = 40,
        .baseSpAttack  = 30,
        .baseSpDefense = 30,
        .baseSpeed     = 25,
        .types = MON_TYPES(TYPE_ROCK, TYPE_BUG),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_VAMPIRE, ABILITY_SOUNDPROOF, ABILITY_SCRAPPY},
        
        .speciesName = _("Larvambre"),
        .categoryName = _("Larve"),
        .height = 10,
        .weight = 500,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_AGGRAMBRE] =
    {
        .baseHP        = 50,
        .baseAttack    = 95,
        .baseDefense   = 70,
        .baseSpAttack  = 95,
        .baseSpDefense = 70,
        .baseSpeed     = 120,
        .types = MON_TYPES(TYPE_ROCK, TYPE_BUG),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_VAMPIRE, ABILITY_SOUNDPROOF, ABILITY_SCRAPPY},
        
        .speciesName = _("Aggrestik"),
        .categoryName = _("Moustique"),
        .height = 20,
        .weight = 860,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_LARVAMBRE

    //P_FAMILY_ALIGRATOR

    [SPECIES_ALIGRATOR] =
    {
        .baseHP        = 54,
        .baseAttack    = 93,
        .baseDefense   = 90,
        .baseSpAttack  = 67,
        .baseSpDefense = 80,
        .baseSpeed     = 126,
        .types = MON_TYPES(TYPE_ROCK, TYPE_GROUND),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_THICK_FAT, ABILITY_SWIFT_SWIM, ABILITY_ROUGH_SKIN},
        
        .speciesName = _("Aligrator"),
        .categoryName = _("Croco Plat"),
        .height = 50,
        .weight = 3300,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_ALIGRATOR

    //P_FAMILY_VIRULOX

    [SPECIES_VIRULOX] =
    {
        .baseHP        = 32,
        .baseAttack    = 82,
        .baseDefense   = 35,
        .baseSpAttack  = 87,
        .baseSpDefense = 37,
        .baseSpeed     = 92,
        .types = MON_TYPES(TYPE_BUG, TYPE_POISON),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_FLARE_BOOST/*, ABILITY_SOIN_BRULURE, ABILITY_BALLIN},
        
        .speciesName = _("Virulox"),
        .categoryName = _("Viral"),
        .height = 8.2,
        .weight = 140,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_RANSOMITE] =
    {
        .baseHP        = 57,
        .baseAttack    = 88,
        .baseDefense   = 60,
        .baseSpAttack  = 119,
        .baseSpDefense = 58,
        .baseSpeed     = 119,
        .types = MON_TYPES(TYPE_BUG, TYPE_FIRE),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_TOXIC_BOOST, ABILITY_TOXIC_HEAL/*, ABILITY_BALLIN},
        
        .speciesName = _("Ransomite"),
        .categoryName = _("Chantage"),
        .height = 13.3,
        .weight = 420,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_VIRULOX

    //P_FAMILY_WORMANES

    [SPECIES_WORMANES] =
    {
        .baseHP        = 80,
        .baseAttack    = 30,
        .baseDefense   = 10,
        .baseSpAttack  = 20,
        .baseSpDefense = 13,
        .baseSpeed     = 11,
        .types = MON_TYPES(TYPE_BUG, TYPE_GHOST),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_INTIMIDATE, ABILITY_SHED_SKIN, ABILITY_SHELL_ARMOR},
        
        .speciesName = _("Wormanes"),
        .categoryName = _("Nuisible"),
        .height = 5.7,
        .weight = 2,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_NYMFICHU] =
    {
        .baseHP        = 60,
        .baseAttack    = 30,
        .baseDefense   = 50,
        .baseSpAttack  = 20,
        .baseSpDefense = 66,
        .baseSpeed     = 10,
        .types = MON_TYPES(TYPE_BUG, TYPE_GHOST),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_INTIMIDATE, ABILITY_SHED_SKIN, ABILITY_SHELL_ARMOR},
        
        .speciesName = _("Nymfichu"),
        .categoryName = _("Inconfort"),
        .height = 10,
        .weight = 8,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_MEMENTOS] =
    {
        .baseHP        = 55,
        .baseAttack    = 65,
        .baseDefense   = 100,
        .baseSpAttack  = 130,
        .baseSpDefense = 80,
        .baseSpeed     = 111,
        .types = MON_TYPES(TYPE_BUG, TYPE_GHOST),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_INTIMIDATE, ABILITY_PRESSURE, ABILITY_COMPOUND_EYES},
        
        .speciesName = _("Mementos"),
        .categoryName = _("Perfide"),
        .height = 18.1,
        .weight = 320,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_WORMANES

    //P_FAMILY_BAGALEVIN

    [SPECIES_BAGALEVIN] =
    {
        .baseHP        = 43,
        .baseAttack    = 14,
        .baseDefense   = 32,
        .baseSpAttack  = 11,
        .baseSpDefense = 23,
        .baseSpeed     = 112,
        .types = MON_TYPES(TYPE_WATER, TYPE FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_DEFIANT, ABILITY_RIVALRY, ABILITY_STAMINA},
        
        .speciesName = _("Bagalevin"),
        .categoryName = _("Bagarreur"),
        .height = 5,
        .weight = 90,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_FRAPOISSON] =
    {
        .baseHP        = 80,
        .baseAttack    = 50,
        .baseDefense   = 70,
        .baseSpAttack  = 50,
        .baseSpDefense = 60,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_DRAGON, TYPE FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_DEFIANT, ABILITY_RIVALRY, ABILITY_STAMINA},
        
        .speciesName = _("Frapoisson"),
        .categoryName = _("Bagarreur"),
        .height = 9,
        .weight = 300,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_DRACOMBAT] =
    {
        .baseHP        = 90,
        .baseAttack    = 138,
        .baseDefense   = 100,
        .baseSpAttack  = 70,
        .baseSpDefense = 67,
        .baseSpeed     = 65,
        .types = MON_TYPES(TYPE_DRAGON, TYPE FIGHTING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_DEFIANT, ABILITY_RIVALRY, ABILITY_SWIFT_SWIM},
        
        .speciesName = _("Dracombat"),
        .categoryName = _("Combattant"),
        .height = 17,
        .weight = 900,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_BAGALEVIN

    //P_FAMILY_LEGENDAIRE_UN

    [SPECIES_UN] =
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_LEGENDAIRE_UN

    //P_FAMILY_LEGENDAIRE_DEUX

    [SPECIES_DEUX] =
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_LEGENDAIRE_DEUX

    //P_FAMILY_LEGENDAIRE_TROIS

    [SPECIES_TROIS] =
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_LEGENDAIRE_TROIS

    //P_FAMILY_PROTYRA

    [SPECIES_PROTYRA] =
    {
        .baseHP        = 30,
        .baseAttack    = 45,
        .baseDefense   = 70,
        .baseSpAttack  = 25,
        .baseSpDefense = 65,
        .baseSpeed     = 25,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_STEEL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_QUARK_DRIVE},
        
        .speciesName = _("Protyra"),
        .categoryName = _("Prototype"),
        .height = 5,
        .weight = 1000,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_MECAREX] =
    {
        .baseHP        = 55,
        .baseAttack    = 60,
        .baseDefense   = 100,
        .baseSpAttack  = 40,
        .baseSpDefense = 86,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_STEEL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_QUARK_DRIVE},
        
        .speciesName = _("Mecarex"),
        .categoryName = _("Update"),
        .height = 15,
        .weight = 1500,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_OMECATYRA] =
    {
        .baseHP        = 90,
        .baseAttack    = 105,
        .baseDefense   = 130,
        .baseSpAttack  = 80,
        .baseSpDefense = 105,
        .baseSpeed     = 90,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_STEEL),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_QUARK_DRIVE},
        
        .speciesName = _("0-Mecatyra"),
        .categoryName = _("Finalisé"),
        .height = 25,
        .weight = 3500,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    [SPECIES_PROGREX] =
    {
        .baseHP        = 45,
        .baseAttack    = 170,
        .baseDefense   = 45,
        .baseSpAttack  = 165,
        .baseSpDefense = 45,
        .baseSpeed     = 130,
        .types = MON_TYPES(TYPE_FIRE, TYPE_ROCK),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_PROTOSYNTHESIS},
        
        .speciesName = _("Progr3x?"),
        .categoryName = _("Déchéance"),
        .height = 25,
        .weight = 2500,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_PROTYRA

    //P_FAMILY_FABULEUX

    [SPECIES_FABULEUX] =
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),
        
        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_FABULEUX

    //P_FAMILY_JUJUBIEL

    [SPECIES_JUJUBIEL]
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),
        
        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
        
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        
        
    },

    //P_FAMILY_JUJUBIEL

    /*
    [SPECIES_] =
    {
        .baseHP        = ,
        .baseAttack    = ,
        .baseDefense   = ,
        .baseSpAttack  = ,
        .baseSpDefense = ,
        .baseSpeed     = ,
        .types = MON_TYPES(),

        .catchRate = ,
        .expYield = ,
        .evYield_SpAttack = ,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(),
        .abilities = { ABILITY_NONE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_,
        .speciesName = _(""),
        .categoryName = _(""),
        .height = ,
        .weight = ,

        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),

        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,

        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 13,
         
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(56, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 4,
        
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_}),
    },

    MON_MALE       0x00
    MON_FEMALE     0xFE
    MON_GENDERLESS 0xFF

    .evYield_HP = ,
    .evYield_Attack = ,
    .evYield_Defense = ,
    .evYield_SpAttack = ,
    .evYield_SpDefense = ,
    .evYield_Speed = ,

    TYPE_NONE             0
    TYPE_NORMAL           1
    TYPE_FIGHTING         2
    TYPE_FLYING           3
    TYPE_POISON           4
    TYPE_GROUND           5
    TYPE_ROCK             6
    TYPE_BUG              7
    TYPE_GHOST            8
    TYPE_STEEL            9
    TYPE_MYSTERY          10
    TYPE_FIRE             11
    TYPE_WATER            12
    TYPE_GRASS            13
    TYPE_ELECTRIC         14
    TYPE_PSYCHIC          15
    TYPE_ICE              16
    TYPE_DRAGON           17
    TYPE_DARK             18
    TYPE_FAIRY            19

    EGG_GROUP_NONE                0
    EGG_GROUP_MONSTER             1
    EGG_GROUP_WATER_1             2 Amphibien, Oiseau, Water Related
    EGG_GROUP_BUG                 3
    EGG_GROUP_FLYING              4
    EGG_GROUP_FIELD               5
    EGG_GROUP_FAIRY               6
    EGG_GROUP_GRASS               7
    EGG_GROUP_HUMAN_LIKE          8
    EGG_GROUP_WATER_3             9  Invertébrés
    EGG_GROUP_MINERAL             10
    EGG_GROUP_AMORPHOUS           11
    EGG_GROUP_WATER_2             12 Poissons, etc
    EGG_GROUP_DITTO               13
    EGG_GROUP_DRAGON              14
    EGG_GROUP_NO_EGGS_DISCOVERED  15

    GROWTH_MEDIUM_FAST  0
    GROWTH_ERRATIC      1
    GROWTH_FLUCTUATING  2
    GROWTH_MEDIUM_SLOW  3
    GROWTH_FAST         4
    GROWTH_SLOW         5

    BODY_COLOR_RED      0
    BODY_COLOR_BLUE     1
    BODY_COLOR_YELLOW   2
    BODY_COLOR_GREEN    3
    BODY_COLOR_BLACK    4
    BODY_COLOR_BROWN    5
    BODY_COLOR_PURPLE   6
    BODY_COLOR_GRAY     7
    BODY_COLOR_WHITE    8
    BODY_COLOR_PINK     9

    // Evolution types
    EVOLUTIONS_END                    0xFFFF // Not an actual evolution, used to mark the end of an evolution array.
    EVO_NONE                          0xFFFE // Not an actual evolution, used to generate offspring that can't evolve into the specified species, like regional forms.
    EVO_FRIENDSHIP                    1      // Pokémon levels up with friendship ≥ 220
    EVO_FRIENDSHIP_DAY                2      // Pokémon levels up during the day with friendship ≥ 220
    EVO_FRIENDSHIP_NIGHT              3      // Pokémon levels up at night with friendship ≥ 220
    EVO_LEVEL                         4      // Pokémon reaches the specified level
    EVO_TRADE                         5      // Pokémon is traded
    EVO_TRADE_ITEM                    6      // Pokémon is traded while it's holding the specified item
    EVO_ITEM                          7      // specified item is used on Pokémon
    EVO_LEVEL_ATK_GT_DEF              8      // Pokémon reaches the specified level with attack > defense
    EVO_LEVEL_ATK_EQ_DEF              9      // Pokémon reaches the specified level with attack = defense
    EVO_LEVEL_ATK_LT_DEF              10     // Pokémon reaches the specified level with attack < defense
    EVO_LEVEL_SILCOON                 11     // Pokémon reaches the specified level with a Silcoon personality value
    EVO_LEVEL_CASCOON                 12     // Pokémon reaches the specified level with a Cascoon personality value
    EVO_LEVEL_NINJASK                 13     // Pokémon reaches the specified level (special value for Ninjask)
    EVO_LEVEL_SHEDINJA                14     // Pokémon reaches the specified level (special value for Shedinja)
    EVO_BEAUTY                        15     // Pokémon levels up with beauty ≥ specified value
    EVO_LEVEL_FEMALE                  16     // Pokémon reaches the specified level, is female
    EVO_LEVEL_MALE                    17     // Pokémon reaches the specified level, is male
    EVO_LEVEL_NIGHT                   18     // Pokémon reaches the specified level, is night
    EVO_LEVEL_DAY                     19     // Pokémon reaches the specified level, is day
    EVO_LEVEL_DUSK                    20     // Pokémon reaches the specified level, is dusk (5-6 P.M)
    EVO_ITEM_HOLD_DAY                 21     // Pokémon levels up, holds specified item at day
    EVO_ITEM_HOLD_NIGHT               22     // Pokémon levels up, holds specified item at night
    EVO_MOVE                          23     // Pokémon levels up, knows specified move
    EVO_FRIENDSHIP_MOVE_TYPE          24     // Pokémon levels up with friendship ≥ 220, knows move with specified type
    EVO_MAPSEC                        25     // Pokémon levels up on specified mapsec
    EVO_ITEM_MALE                     26     // specified item is used on a male Pokémon
    EVO_ITEM_FEMALE                   27     // specified item is used on a female Pokémon
    EVO_LEVEL_RAIN                    28     // Pokémon reaches the specified level during rain in the overworld
    EVO_SPECIFIC_MON_IN_PARTY         29     // Pokémon levels up with a specified Pokémon in party
    EVO_LEVEL_DARK_TYPE_MON_IN_PARTY  30     // Pokémon reaches the specified level with a Dark Type Pokémon in party
    EVO_TRADE_SPECIFIC_MON            31     // Pokémon is traded for a specified Pokémon
    EVO_SPECIFIC_MAP                  32     // Pokémon levels up on specified map
    EVO_LEVEL_NATURE_AMPED            33     // Pokémon reaches the specified level, it has a Hardy, Brave, Adamant, Naughty, Docile, Impish, Lax, Hasty, Jolly, Naive, Rash, Sassy, or Quirky nature.
    EVO_LEVEL_NATURE_LOW_KEY          34     // Pokémon reaches the specified level, it has a Lonely, Bold, Relaxed, Timid, Serious, Modest, Mild, Quiet, Bashful, Calm, Gentle, or Careful nature.
    EVO_CRITICAL_HITS                 35     // Pokémon performs specified number of critical hits in one battle
    EVO_SCRIPT_TRIGGER_DMG            36     // Pokémon has specified HP below max, then player interacts trigger
    EVO_DARK_SCROLL                   37     // interacts with Scroll of Darkness
    EVO_WATER_SCROLL                  38     // interacts with Scroll of Waters
    EVO_ITEM_NIGHT                    39     // specified item is used on Pokémon, is night
    EVO_ITEM_DAY                      40     // specified item is used on Pokémon, is day
    EVO_ITEM_HOLD                     41     // Pokémon levels up, holds specified item
    EVO_LEVEL_FOG                     42     // Pokémon reaches the specified level during fog in the overworld
    EVO_MOVE_TWO_SEGMENT              43     // Pokémon levels up, knows specified move, has a personality value with a modulus of 0
    EVO_MOVE_THREE_SEGMENT            44     // Pokémon levels up, knows specified move, has a personality value with a modulus of 1-99
    EVO_LEVEL_FAMILY_OF_THREE         45     // Pokémon reaches the specified level in battle with a personality value with a modulus of 0
    EVO_LEVEL_FAMILY_OF_FOUR          46     // Pokémon reaches the specified level in battle with a personality value with a modulus of 1-99
    EVO_USE_MOVE_TWENTY_TIMES         47     // Pokémon levels up after having used a move for at least 20 times
    EVO_RECOIL_DAMAGE_MALE            48     // Pokémon levels up after having suffered specified amount of non-fainting recoil damage as a male
    EVO_RECOIL_DAMAGE_FEMALE          49     // Pokémon levels up after having suffered specified amount of non-fainting recoil damage as a female
    EVO_ITEM_COUNT_999                50     // Pokémon levels up after trainer has collected 999 of a specific item
    EVO_DEFEAT_THREE_WITH_ITEM        51     // Pokémon levels up after having defeat 3 Pokémon of the same species holding the specified item
    EVO_OVERWORLD_STEPS               52     // Pokémon levels up after having taken a specific amount of steps in the overworld (or as the party lead if OW_FOLLOWERS_ENABLED is FALSE) without switching
    */

    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        //.frontPicFemale = gMonFrontPic_Placeholder,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_PlaceholderF,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        //.paletteFemale = gMonPalette_PlaceholderF,
        //.shinyPaletteFemale = gMonShinyPalette_PlaceholderF,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //.iconSpriteFemale = gMonIcon_QuestionMarkF,
        //.iconPalIndexFemale = 1,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        .allPerfectIVs = TRUE,
    },
    */
    /*
    [SPECIES_DAVID] =
    {
        .baseHP        = 69,
        .baseAttack    = 96,
        .baseDefense   = 69,
        .baseSpAttack  = 96,
        .baseSpDefense = 69,
        .baseSpeed     = 96,
        .types = MON_TYPES(TYPE_FLYING),
        .catchRate = ,
        .expYield = ,
        
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = ,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_,
        
        .abilities = {ABILITY_INTIMIDATE, ABILITY_RUN_AWAY, ABILITY_HUSTLE},
        
        .speciesName = _("DAVID"),
        .categoryName = _("Poulet?!"),
        .height = 6.6,
        .weight = 50,
        //data
        .evYield_ = ,
        .eggGroups = MON_EGG_GROUPS(),
        .bodyColor = BODY_COLOR_,
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_,
        .description = COMPOUND_STRING(
            " \n"
            "Placeholder\n"
            " \n"
            " "),
        .pokemonScale = 255,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        //graphics
        .frontPic = gMonFrontPic_Placeholder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
         
        .backPic = gMonBackPic_Placeholder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Placeholder,
        .shinyPalette = gMonShinyPalette_Placeholder,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //learnsets
        .levelUpLearnset = sBulbasaurLevelUpLearnset,
        .teachableLearnset = sBulbasaurTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE}),
    },

    //P_FAMILY_DAVID
    */
};
