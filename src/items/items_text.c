#include <pokeagb/pokeagb.h>

//Items Name
const pchar item_names[][15] = {
    _("-----"),
    _("Poke Doll"),
    _("Fluffy Tail"),
    _("Oval Stone"),
    _("Douse Drive"),
    _("Shock Drive"),
    _("Burn Drive"),
    _("Chill Drive"),
    _("Cheri Berry"),
    _("Chesto Berry"),
    _("Pecha Berry"),
    _("Rawst Berry"),
    _("Aspear Berry"),
    _("Leppa Berry"),
    _("Oran Berry"),
    _("Persim Berry"),
    _("Lum Berry"),
    _("Sitrus Berry"),
    _("Figy Berry"),
    _("Wiki Berry"),
    _("Mago Berry"),
    _("Aguav Berry"),
    _("Iapapa Berry"),
    _("Razz Berry"),
    _("Bluk Berry"),
    _("Nanab Berry"),
    _("Wepear Berry"),
    _("Pinap Berry"),
    _("Pomeg Berry"),
    _("Kelpsy Berry"),
    _("Qualot Berry"),
    _("Hondew Berry"),
    _("Grepa Berry"),
    _("Tamato Berry"),
    _("Cornn Berry"),
    _("Magost Berry"),
    _("Rabuta Berry"),
    _("Nomel Berry"),
    _("Spelon Berry"),
    _("Pamtre Berry"),
    _("Watmel Berry"),
    _("Durin Berry"),
    _("Belue Berry"),
    _("Occa Berry"),
    _("Passho Berry"),
    _("Wacan Berry"),
    _("Rindo Berry"),
    _("Yache Berry"),
    _("Chople Berry"),
    _("Kebia Berry"),
    _("Shuca Berry"),
    _("Coba Berry"),
    _("Payapa Berry"),
    _("Tanga Berry"),
    _("Charti Berry"),
    _("Kasib Berry"),
    _("Haban Berry"),
    _("Colbur Berry"),
    _("Babiri Berry"),
    _("Chilan Berry"),
    _("Liechi Berry"),
    _("Ganlon Berry"),
    _("Salac Berry"),
    _("Petaya Berry"),
    _("Apicot Berry"),
    _("Lansat Berry"),
    _("Starf Berry"),
    _("Enigma Berry"),
    _("Micle Berry"),
    _("Custap Berry"),
    _("Jaboca Berry"),
    _("Rowap Berry"),
    _("Bright Powder"),
    _("White Herb"),
    _("Macho Brace"),
    _("Exp. Share"),
    _("Quick Claw"),
    _("Mental Herb"),
    _("Choice Band"),
    _("King's Tock"),
    _("Silver Powder"),
    _("Amulet Coin"),
    _("Soul Dew"),
    _("Deep Sea Tooth"),
    _("Deep Sea Scale"),
    _("Smoke Ball"),
    _("Focus Band"),
    _("Lucky Egg"),
    _("Scope Lens"),
    _("Metal Coat"),
    _("Leftovers"),
    _("Dragon Scale"),
    _("Light Ball"),
    _("Soft Sand"),
    _("Hard Stone"),
    _("Miracle Seed"),
    _("Black Glasses"),
    _("Black Belt"),
    _("Magnet"),
    _("Mystic Water"),
    _("Sharp Beak"),
    _("Poison Barb"),
    _("Never Melt Ice"),
    _("Spell Tag"),
    _("Twisted Spoon"),
    _("Charcoal"),
    _("Dragon Fang"),
    _("Silk Scarf"),
    _("Upgrade"),
    _("Shell Bell"),
    _("Sea Incense"),
    _("Lax Incense"),
    _("Lucky Punch"),
    _("Metal Powder"),
    _("Thick Club"),
    _("Stick"),
    _("Wide Lens"),
    _("Muscle Band"),
    _("Wise Glasses"),
    _("Expert Belt"),
    _("Life Orb"),
    _("Power Herb"),
    _("Toxic Orb"),
    _("Flame Orb"),
    _("Quick Powder"),
    _("Focus Sash"),
    _("Zoom Lens"),
    _("Metronome"),
    _("Iron Ball"),
    _("Lagging Tail"),
    _("Destiny Knot"),
    _("Black Sludge"),
    _("Choice Scarf"),
    _("Sticky Barb"),
    _("Power Bracer"),
    _("Power Belt"),
    _("Power Lens"),
    _("Power Band"),
    _("Power Anklet"),
    _("Power Weight"),
    _("Shed Shell"),
    _("Big Root"),
    _("Choice Specs"),
    _("Flame Plate"),
    _("Splash Plate"),
    _("Zap Plate"),
    _("Meadow Plate"),
    _("Icicle Plate"),
    _("Fist Plate"),
    _("Toxic Plate"),
    _("Earth Plate"),
    _("Sky Plate"),
    _("Mind Plate"),
    _("Insect Plate"),
    _("Stone Plate"),
    _("Spooky Plate"),
    _("Draco Plate"),
    _("Dread Plate"),
    _("Iron Plate"),
    _("Odd Incense"),
    _("Rock Incense"),
    _("Full Incense"),
    _("Wave Incense"),
    _("Rose Incense"),
    _("Luck Incense"),
    _("Pure Incense"),
    _("Protector"),
    _("Electirizer"),
    _("Magmarizer"),
    _("Dubious Disc"),
    _("Reaper Cloth"),
    _("Razor Claw"),
    _("Razor Fang"),
    _("Red Orb"),
    _("Blue Orb"),
    _("Prism Scale"),
    _("Eviolite"),
    _("Float Stone"),
    _("Rocky Helmet"),
    _("Air Balloon"),
    _("Red Card"),
    _("Ring Target"),
    _("Absorb Bulb"),
    _("Cell Battery"),
    _("Eject Button"),
    _("Fire Gem"),
    _("Water Gem"),
    _("Electric Gem"),
    _("Grass Gem"),
    _("Ice Gem"),
    _("Fighting Gem"),
    _("Poison Gem"),
    _("Ground Gem"),
    _("Flying Gem"),
    _("Psychic Gem"),
    _("Bug Gem"),
    _("Rock Gem"),
    _("Ghost Gem"),
    _("Dragon Gem"),
    _("Dark Gem"),
    _("Steel Gem"),
    _("Normal Gem"),
    _("Poke Toy"),
    _("Weakness Policy"),
    _("Assault Vest"),
    _("Pixie Plate"),
    _("Whipped Dream"),
    _("Sachet"),
    _("Luminous Moss"),
    _("Snow Ball"),
    _("Safety Goggles"),
    _("Roseli Berry"),
    _("Kee Berry"),
    _("Maranga Berry"),
    _("Fairy Gem"),
    _("Binding Band"),
    _("Damp Rock"),
    _("Grip Claw"),
    _("Heat Rock"),
    _("Icy Rock"),
    _("Light Clay"),
    _("Smooth Rock"),
    _("Terrain Extender"),
    _("Adrenaline Orb"),
    _("Terrain Extender"),
    _("Protective Pads"),
    _("Electric Seed"),
    _("Psychic Seed"),
    _("Misty Seed"),
    _("Grassy Seed"),
    _("Fighting Memory"),
    _("Flying Memory"),
    _("Poison Memory"),
    _("Ground Memory"),
    _("Rock Memory"),
    _("Bug Memory"),
    _("Ghost Memory"),
    _("Steel Memory"),
    _("Fire Memory"),
    _("Water Memory"),
    _("Grass Memory"),
    _("Electric Memory"),
    _("Psychic Memory"),
    _("Ice Memory"),
    _("Dragon Memory"),
    _("Dark Memory"),
    _("Fairy Memory")
};
