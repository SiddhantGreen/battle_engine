#include <pokeagb/pokeagb.h>
#include "moves.h"


pchar Pound_desc[] = _"No additional effect.";
pchar Karate_Chop_desc[] = _"High critical hit ratio.";
pchar Double_Slap_desc[] = _"Hits 2-5 times in one turn.";
pchar Comet_Punch_desc[] = _"Hits 2-5 times in one turn.";
pchar Mega_Punch_desc[] = _"No additional effect.";
pchar Pay_Day_desc[] = _"Scatters coins.";
pchar Fire_Punch_desc[] = _"10% chance to burn the target.";
pchar Ice_Punch_desc[] = _"10% chance to freeze the target.";
pchar Thunder_Punch_desc[] = _"10% chance to paralyze the target.";
pchar Scratch_desc[] = _"No additional effect.";
pchar Vice_Grip_desc[] = _"No additional effect.";
pchar Guillotine_desc[] = _"OHKOs the target. Fails if user is a lower level.";
pchar Razor_Wind_desc[] = _"Charges then hits foe(s) turn 2. High crit ratio.";
pchar Swords_Dance_desc[] = _"Raises the user‘s Attack by 2.";
pchar Cut_desc[] = _"No additional effect.";
pchar Gust_desc[] = _"Power doubles during Fly Bounce and Sky Drop.";
pchar Wing_Attack_desc[] = _"No additional effect.";
pchar Whirlwind_desc[] = _"Forces the target to switch to a random ally.";
pchar Fly_desc[] = _"Flies up on first turn then strikes the next turn.";
pchar Bind_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Slam_desc[] = _"No additional effect.";
pchar Vine_Whip_desc[] = _"No additional effect.";
pchar Stomp_desc[] = _"30% chance to flinch the target.";
pchar Double_Kick_desc[] = _"Hits 2 times in one turn.";
pchar Mega_Kick_desc[] = _"No additional effect.";
pchar Jump_Kick_desc[] = _"User is hurt by 50% of its max HP if it misses.";
pchar Rolling_Kick_desc[] = _"30% chance to flinch the target.";
pchar Sand_Attack_desc[] = _"Lowers the target‘s accuracy by 1.";
pchar Headbutt_desc[] = _"30% chance to flinch the target.";
pchar Horn_Attack_desc[] = _"No additional effect.";
pchar Fury_Attack_desc[] = _"Hits 2-5 times in one turn.";
pchar Horn_Drill_desc[] = _"OHKOs the target. Fails if user is a lower level.";
pchar Tackle_desc[] = _"No additional effect.";
pchar Body_Slam_desc[] = _"30% chance to paralyze the target.";
pchar Wrap_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Take_Down_desc[] = _"Has 1/4 recoil.";
pchar Thrash_desc[] = _"Lasts 2-3 turns. Confuses the user afterwards.";
pchar Double_Edge_desc[] = _"Has 33% recoil.";
pchar Tail_Whip_desc[] = _"Lowers the foe(s) Defense by 1.";
pchar Poison_Sting_desc[] = _"30% chance to poison the target.";
pchar Twineedle_desc[] = _"Hits 2 times. Each hit has 20% chance to poison.";
pchar Pin_Missile_desc[] = _"Hits 2-5 times in one turn.";
pchar Leer_desc[] = _"Lowers the foe(s) Defense by 1.";
pchar Bite_desc[] = _"30% chance to flinch the target.";
pchar Growl_desc[] = _"Lowers the foe(s) Attack by 1.";
pchar Roar_desc[] = _"Forces the target to switch to a random ally.";
pchar Sing_desc[] = _"Puts the target to sleep.";
pchar Supersonic_desc[] = _"Confuses the target.";
pchar Sonic_Boom_desc[] = _"Always does 20 HP of damage.";
pchar Disable_desc[] = _"For 4 turns disables the target‘s last move used.";
pchar Acid_desc[] = _"10% chance to lower the foe(s) Sp. Def by 1.";
pchar Ember_desc[] = _"10% chance to burn the target.";
pchar Flamethrower_desc[] = _"10% chance to burn the target.";
pchar Mist_desc[] = _"For 5 turns protects user‘s party from stat drops.";
pchar Water_Gun_desc[] = _"No additional effect.";
pchar Hydro_Pump_desc[] = _"No additional effect.";
pchar Surf_desc[] = _"Hits adjacent Pokemon. Power doubles on Dive.";
pchar Ice_Beam_desc[] = _"10% chance to freeze the target.";
pchar Blizzard_desc[] = _"10% chance to freeze the foe(s).";
pchar Psybeam_desc[] = _"10% chance to confuse the target.";
pchar Bubble_Beam_desc[] = _"10% chance to lower the target‘s Speed by 1.";
pchar Aurora_Beam_desc[] = _"10% chance to lower the foe‘s Attack by 1.";
pchar Hyper_Beam_desc[] = _"User cannot move next turn.";
pchar Peck_desc[] = _"No additional effect.";
pchar Drill_Peck_desc[] = _"No additional effect.";
pchar Submission_desc[] = _"Has 1/4 recoil.";
pchar Low_Kick_desc[] = _"More power the heavier the target.";
pchar Counter_desc[] = _"If hit by physical attack returns double damage.";
pchar Seismic_Toss_desc[] = _"Does damage equal to the user‘s level.";
pchar Strength_desc[] = _"No additional effect.";
pchar Absorb_desc[] = _"User recovers 50% of the damage dealt.";
pchar Mega_Drain_desc[] = _"User recovers 50% of the damage dealt.";
pchar Leech_Seed_desc[] = _"1/8 of target‘s HP is restored to user every turn.";
pchar Growth_desc[] = _"Raises user‘s Attack and SpAtk by 1, or 2 in Sun.";
pchar Razor_Leaf_desc[] = _"High critical hit ratio. Hits adjacent foes.";
pchar Solar_Beam_desc[] = _"Charges turn 1. Hits turn 2. No charge in sunlight.";
pchar Poison_Powder_desc[] = _"Poisons the target.";
pchar Stun_Spore_desc[] = _"Paralyzes the target.";
pchar Sleep_Powder_desc[] = _"Puts the target to sleep.";
pchar Petal_Dance_desc[] = _"Lasts 2-3 turns. Confuses the user afterwards.";
pchar String_Shot_desc[] = _"Lowers the foe(s) Speed by 2.";
pchar Dragon_Rage_desc[] = _"Always does 40 HP of damage.";
pchar Fire_Spin_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Thunder_Shock_desc[] = _"10% chance to paralyze the target.";
pchar Thunderbolt_desc[] = _"10% chance to paralyze the target.";
pchar Thunder_Wave_desc[] = _"Paralyzes the target.";
pchar Thunder_desc[] = _"30% chance to paralyze target. Can‘t miss in rain.";
pchar Rock_Throw_desc[] = _"No additional effect.";
pchar Earthquake_desc[] = _"Hits adjacent Pokemon. Power doubles on Dig.";
pchar Fissure_desc[] = _"OHKOs the target. Fails if user is a lower level.";
pchar Dig_desc[] = _"Digs underground turn 1 strikes turn 2.";
pchar Toxic_desc[] = _"Badly poisons the target.";
pchar Confusion_desc[] = _"10% chance to confuse the target.";
pchar Psychic_desc[] = _"10% chance to lower the target‘s Sp. Def by 1.";
pchar Hypnosis_desc[] = _"Puts the target to sleep.";
pchar Meditate_desc[] = _"Raises the user‘s Attack by 1.";
pchar Agility_desc[] = _"Raises the user‘s Speed by 2.";
pchar Quick_Attack_desc[] = _"Usually goes first.";
pchar Rage_desc[] = _"Raises the user‘s Attack by 1 if hit during use.";
pchar Teleport_desc[] = _"Flee from wild Pokemon battles.";
pchar Night_Shade_desc[] = _"Does damage equal to the user‘s level.";
pchar Mimic_desc[] = _"The last move the target used replaces this one.";
pchar Screech_desc[] = _"Lowers the target‘s Defense by 2.";
pchar Double_Team_desc[] = _"Raises the user‘s evasiveness by 1.";
pchar Recover_desc[] = _"Heals the user by 50% of its max HP.";
pchar Harden_desc[] = _"Raises the user‘s Defense by 1.";
pchar Minimize_desc[] = _"Raises the user‘s evasiveness by 2.";
pchar Smokescreen_desc[] = _"Lowers the target‘s accuracy by 1.";
pchar Confuse_Ray_desc[] = _"Confuses the target.";
pchar Withdraw_desc[] = _"Raises the user‘s Defense by 1.";
pchar Defense_Curl_desc[] = _"Raises the user‘s Defense by 1.";
pchar Barrier_desc[] = _"Raises the user‘s Defense by 2.";
pchar Light_Screen_desc[] = _"For 5 turns special damage to allies is halved.";
pchar Haze_desc[] = _"Eliminates all stat changes.";
pchar Reflect_desc[] = _"For 5 turns physical damage to allies is halved.";
pchar Focus_Energy_desc[] = _"Raises the user‘s critical hit ratio by 2.";
pchar Bide_desc[] = _"Waits 2 turns- deals double the damage taken.";
pchar Metronome_desc[] = _"Picks a random move.";
pchar Mirror_Move_desc[] = _"User uses the target‘s last used move against it.";
pchar Self_Destruct_desc[] = _"Hits adjacent Pokemon. The user faints.";
pchar Egg_Bomb_desc[] = _"No additional effect.";
pchar Lick_desc[] = _"30% chance to paralyze the target.";
pchar Smog_desc[] = _"40% chance to poison the target.";
pchar Sludge_desc[] = _"30% chance to poison the target.";
pchar Bone_Club_desc[] = _"10% chance to flinch the target.";
pchar Fire_Blast_desc[] = _"10% chance to burn the target.";
pchar Waterfall_desc[] = _"20% chance to flinch the target.";
pchar Clamp_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Swift_desc[] = _"This move does not check accuracy. Hits foes.";
pchar Skull_Bash_desc[] = _"Raises user‘s Defense by 1 on turn 1. Hits turn 2.";
pchar Spike_Cannon_desc[] = _"Hits 2-5 times in one turn.";
pchar Constrict_desc[] = _"10% chance to lower the target‘s Speed by 1.";
pchar Amnesia_desc[] = _"Raises the user‘s Sp. Def by 2.";
pchar Kinesis_desc[] = _"Lowers the target‘s accuracy by 1.";
pchar Soft_Boiled_desc[] = _"Heals the user by 50% of its max HP.";
pchar High_Jump_Kick_desc[] = _"User is hurt by 50% of its max HP if it misses.";
pchar Glare_desc[] = _"Paralyzes the target.";
pchar Dream_Eater_desc[] = _"User gains 1/2 HP inflicted. Sleeping target only.";
pchar Poison_Gas_desc[] = _"Poisons the foe(s).";
pchar Barrage_desc[] = _"Hits 2-5 times in one turn.";
pchar Leech_Life_desc[] = _"User recovers 50% of the damage dealt.";
pchar Lovely_Kiss_desc[] = _"Puts the target to sleep.";
pchar Sky_Attack_desc[] = _"Charges then hits turn 2. 30% flinch. High crit.";
pchar Transform_desc[] = _"Copies target‘s stats moves types and Ability.";
pchar Bubble_desc[] = _"10% chance to lower the foe(s) Speed by 1.";
pchar Dizzy_Punch_desc[] = _"20% chance to confuse the target.";
pchar Spore_desc[] = _"Puts the target to sleep.";
pchar Flash_desc[] = _"Lowers the target‘s accuracy by 1.";
pchar Psywave_desc[] = _"Random damage equal to 0.5x-1.5x user‘s level.";
pchar Splash_desc[] = _"Does nothing (but we still love it).";
pchar Acid_Armor_desc[] = _"Raises the user‘s Defense by 2.";
pchar Crabhammer_desc[] = _"High critical hit ratio.";
pchar Explosion_desc[] = _"Hits adjacent Pokemon. The user faints.";
pchar Fury_Swipes_desc[] = _"Hits 2-5 times in one turn.";
pchar Bonemerang_desc[] = _"Hits 2 times in one turn.";
pchar Rest_desc[] = _"User sleeps 2 turns and restores HP and status.";
pchar Rock_Slide_desc[] = _"30% chance to flinch the foe(s).";
pchar Hyper_Fang_desc[] = _"10% chance to flinch the target.";
pchar Sharpen_desc[] = _"Raises the user‘s Attack by 1.";
pchar Conversion_desc[] = _"Changes user‘s type to match its first move.";
pchar Tri_Attack_desc[] = _"20% chance to paralyze or burn or freeze target.";
pchar Super_Fang_desc[] = _"Does damage equal to 1/2 target‘s current HP.";
pchar Slash_desc[] = _"High critical hit ratio.";
pchar Substitute_desc[] = _"User takes 1/4 its max HP to put in a Substitute.";
pchar Struggle_desc[] = _"User loses 25% of its max HP as recoil.";
pchar Sketch_desc[] = _"Permanently copies the last move target used.";
pchar Triple_Kick_desc[] = _"Hits 3 times. Each hit can miss but power rises.";
pchar Thief_desc[] = _"If the user has no item it steals the target‘s.";
pchar Spider_Web_desc[] = _"The target cannot switch out.";
pchar Mind_Reader_desc[] = _"User‘s next move will not miss the target.";
pchar Nightmare_desc[] = _"A sleeping target is hurt by 1/4 max HP per turn.";
pchar Flame_Wheel_desc[] = _"10% chance to burn the target. Thaws user.";
pchar Snore_desc[] = _"User must be asleep. 30% chance to flinch target.";
pchar Curse_desc[] = _"Curses if Ghost else +1 Atk +1 Def -1 Spe.";
pchar Flail_desc[] = _"More power the less HP the user has left.";
pchar Conversion_2_desc[] = _"Changes user‘s type to resist target‘s last move.";
pchar Aeroblast_desc[] = _"High critical hit ratio.";
pchar Cotton_Spore_desc[] = _"Lowers the target‘s Speed by 2.";
pchar Reversal_desc[] = _"More power the less HP the user has left.";
pchar Spite_desc[] = _"Lowers the PP of the target‘s last move by 4.";
pchar Powder_Snow_desc[] = _"10% chance to freeze the foe(s).";
pchar Protect_desc[] = _"Prevents moves from affecting the user this turn.";
pchar Mach_Punch_desc[] = _"Usually goes first.";
pchar Scary_Face_desc[] = _"Lowers the target‘s Speed by 2.";
pchar Feint_Attack_desc[] = _"This move does not check accuracy.";
pchar Sweet_Kiss_desc[] = _"Confuses the target.";
pchar Belly_Drum_desc[] = _"User loses 50% max HP. Maximizes Attack.";
pchar Sludge_Bomb_desc[] = _"30% chance to poison the target.";
pchar Mud_Slap_desc[] = _"100% chance to lower the target‘s accuracy by 1.";
pchar Octazooka_desc[] = _"50% chance to lower the target‘s accuracy by 1.";
pchar Spikes_desc[] = _"Hurts grounded foes on switch-in. Max 3 layers.";
pchar Zap_Cannon_desc[] = _"100% chance to paralyze the target.";
pchar Foresight_desc[] = _"Fighting Normal hit Ghost. Evasiveness ignored.";
pchar Destiny_Bond_desc[] = _"If an opponent knocks out the user it also faints.";
pchar Perish_Song_desc[] = _"All active Pokemon will faint in 3 turns.";
pchar Icy_Wind_desc[] = _"100% chance to lower the foe(s) Speed by 1.";
pchar Detect_desc[] = _"Prevents moves from affecting the user this turn.";
pchar Bone_Rush_desc[] = _"Hits 2-5 times in one turn.";
pchar Lock_On_desc[] = _"User‘s next move will not miss the target.";
pchar Outrage_desc[] = _"Lasts 2-3 turns. Confuses the user afterwards.";
pchar Sandstorm_desc[] = _"For 5 turns a sandstorm rages.";
pchar Giga_Drain_desc[] = _"User recovers 50% of the damage dealt.";
pchar Endure_desc[] = _"The user survives the next hit with at least 1 HP.";
pchar Charm_desc[] = _"Lowers the target‘s Attack by 2.";
pchar Rollout_desc[] = _"Power doubles with each hit. Repeats for 5 turns.";
pchar False_Swipe_desc[] = _"Always leaves the target with at least 1 HP.";
pchar Swagger_desc[] = _"Raises the target‘s Attack by 2 and confuses it.";
pchar Milk_Drink_desc[] = _"Heals the user by 50% of its max HP.";
pchar Spark_desc[] = _"30% chance to paralyze the target.";
pchar Fury_Cutter_desc[] = _"Power doubles with each hit up to 160.";
pchar Steel_Wing_desc[] = _"10% chance to raise the user‘s Defense by 1.";
pchar Mean_Look_desc[] = _"The target cannot switch out.";
pchar Attract_desc[] = _"A target of the opposite gender gets infatuated.";
pchar Sleep_Talk_desc[] = _"User must be asleep. Uses another known move.";
pchar Heal_Bell_desc[] = _"Cures the user‘s party of all status conditions.";
pchar Return_desc[] = _"Max 102 power at maximum Happiness.";
pchar Present_desc[] = _"40 80 120 power or heals target by 1/4 max HP.";
pchar Frustration_desc[] = _"Max 102 power at minimum Happiness.";
pchar Safeguard_desc[] = _"For 5 turns protects user‘s party from status.";
pchar Pain_Split_desc[] = _"Shares HP of user and target equally.";
pchar Sacred_Fire_desc[] = _"50% chance to burn the target. Thaws user.";
pchar Magnitude_desc[] = _"Hits adjacent Pokemon. Power varies- 2x on Dig.";
pchar Dynamic_Punch_desc[] = _"100% chance to confuse the target.";
pchar Megahorn_desc[] = _"No additional effect.";
pchar Dragon_Breath_desc[] = _"30% chance to paralyze the target.";
pchar Baton_Pass_desc[] = _"User switches passing stat changes and more.";
pchar Encore_desc[] = _"The target repeats its last move for 3 turns.";
pchar Pursuit_desc[] = _"Power doubles if a foe is switching out.";
pchar Rapid_Spin_desc[] = _"Frees user from hazards/partial trap/Leech Seed.";
pchar Sweet_Scent_desc[] = _"Lowers the foe(s) evasion by 2.";
pchar Iron_Tail_desc[] = _"30% chance to lower the target‘s Defense by 1.";
pchar Metal_Claw_desc[] = _"10% chance to raise the user‘s Attack by 1.";
pchar Vital_Throw_desc[] = _"This move does not check accuracy. Goes last.";
pchar Morning_Sun_desc[] = _"Heals the user by a weather-dependent amount.";
pchar Synthesis_desc[] = _"Heals the user by a weather-dependent amount.";
pchar Moonlight_desc[] = _"Heals the user by a weather-dependent amount.";
pchar Hidden_Power_desc[] = _"Varies in type based on the user‘s IVs.";
pchar Cross_Chop_desc[] = _"High critical hit ratio.";
pchar Twister_desc[] = _"20% chance to flinch the foe(s).";
pchar Rain_Dance_desc[] = _"For 5 turns heavy rain powers Water moves.";
pchar Sunny_Day_desc[] = _"For 5 turns intense sunlight powers Fire moves.";
pchar Crunch_desc[] = _"20% chance to lower the target‘s Defense by 1.";
pchar Mirror_Coat_desc[] = _"If hit by special attack returns double damage.";
pchar Psych_Up_desc[] = _"Copies the target‘s current stat stages.";
pchar Extreme_Speed_desc[] = _"Nearly always goes first.";
pchar Ancient_Power_desc[] = _"10% chance to raise all stats by 1 (not acc/eva).";
pchar Shadow_Ball_desc[] = _"20% chance to lower the target‘s Sp. Def by 1.";
pchar Future_Sight_desc[] = _"Hits two turns after being used.";
pchar Rock_Smash_desc[] = _"50% chance to lower the target‘s Defense by 1.";
pchar Whirlpool_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Beat_Up_desc[] = _"All healthy allies aid in damaging the target.";
pchar Fake_Out_desc[] = _"Hits first. First turn out only. 100% flinch chance.";
pchar Uproar_desc[] = _"Lasts 3 turns. Active Pokemon cannot fall asleep.";
pchar Stockpile_desc[] = _"Raises user‘s Defense Sp. Def by 1. Max 3 uses.";
pchar Spit_Up_desc[] = _"More power with more uses of Stockpile.";
pchar Swallow_desc[] = _"Heals the user based on uses of Stockpile.";
pchar Heat_Wave_desc[] = _"10% chance to burn the foe(s).";
pchar Hail_desc[] = _"For 5 turns hail crashes down.";
pchar Torment_desc[] = _"Target can‘t select the same move twice in a row.";
pchar Flatter_desc[] = _"Raises the target‘s Sp. Atk by 1 and confuses it.";
pchar Will_O_Wisp_desc[] = _"Burns the target.";
pchar Memento_desc[] = _"Lowers target‘s Attack Sp. Atk by 2. User faints.";
pchar Facade_desc[] = _"Power doubles if user is burn/poison/paralyzed.";
pchar Focus_Punch_desc[] = _"Fails if the user takes damage before it hits.";
pchar Smelling_Salts_desc[] = _"Power doubles if target is paralyzed and cures it.";
pchar Follow_Me_desc[] = _"The foes‘ moves target the user on the turn used.";
pchar Nature_Power_desc[] = _"Attack depends on terrain (default Tri Attack).";
pchar Charge_desc[] = _"Boosts next Electric move and user‘s Sp. Def by 1.";
pchar Taunt_desc[] = _"For 3 turns the target can‘t use status moves.";
pchar Helping_Hand_desc[] = _"One adjacent ally‘s move power is 1.5x this turn.";
pchar Trick_desc[] = _"User switches its held item with the target‘s.";
pchar Role_Play_desc[] = _"User replaces its Ability with the target‘s.";
pchar Wish_desc[] = _"Next turn 50% of the user‘s max HP is restored.";
pchar Assist_desc[] = _"Uses a random move known by a team member.";
pchar Ingrain_desc[] = _"User recovers 1/16 max HP per turn. Traps user.";
pchar Superpower_desc[] = _"Lowers the user‘s Attack and Defense by 1.";
pchar Magic_Coat_desc[] = _"Bounces back certain non-damaging moves.";
pchar Recycle_desc[] = _"Restores the item the user last used.";
pchar Revenge_desc[] = _"Power doubles if user is damaged by the target.";
pchar Brick_Break_desc[] = _"Destroys screens unless the target is immune.";
pchar Yawn_desc[] = _"Puts the target to sleep after 1 turn.";
pchar Knock_Off_desc[] = _"1.5x damage if foe holds an item. Removes item.";
pchar Endeavor_desc[] = _"Lowers the target‘s HP to the user‘s HP.";
pchar Eruption_desc[] = _"Less power as user‘s HP decreases. Hits foe(s).";
pchar Skill_Swap_desc[] = _"The user and the target trade Abilities.";
pchar Imprison_desc[] = _"No foe can use any move known by the user.";
pchar Refresh_desc[] = _"User cures its burn poison or paralysis.";
pchar Grudge_desc[] = _"If the user faints the attack used loses all its PP.";
pchar Snatch_desc[] = _"User steals certain support moves to use itself.";
pchar Secret_Power_desc[] = _"Effect varies with terrain. (30% paralysis chance)";
pchar Dive_desc[] = _"Dives underwater turn 1 strikes turn 2.";
pchar Arm_Thrust_desc[] = _"Hits 2-5 times in one turn.";
pchar Camouflage_desc[] = _"Changes user‘s type by terrain (default Normal).";
pchar Tail_Glow_desc[] = _"Raises the user‘s Sp. Atk by 3.";
pchar Luster_Purge_desc[] = _"50% chance to lower the target‘s Sp. Def by 1.";
pchar Mist_Ball_desc[] = _"50% chance to lower the target‘s Sp. Atk by 1.";
pchar Feather_Dance_desc[] = _"Lowers the target‘s Attack by 2.";
pchar Teeter_Dance_desc[] = _"Confuses adjacent Pokemon.";
pchar Blaze_Kick_desc[] = _"High critical hit ratio. 10% chance to burn.";
pchar Mud_Sport_desc[] = _"For 5 turns Electric-type attacks have 1/3 power.";
pchar Ice_Ball_desc[] = _"Power doubles with each hit. Repeats for 5 turns.";
pchar Needle_Arm_desc[] = _"30% chance to flinch the target.";
pchar Slack_Off_desc[] = _"Heals the user by 50% of its max HP.";
pchar Hyper_Voice_desc[] = _"No additional effect. Hits adjacent foes.";
pchar Poison_Fang_desc[] = _"50% chance to badly poison the target.";
pchar Crush_Claw_desc[] = _"50% chance to lower the target‘s Defense by 1.";
pchar Blast_Burn_desc[] = _"User cannot move next turn.";
pchar Hydro_Cannon_desc[] = _"User cannot move next turn.";
pchar Meteor_Mash_desc[] = _"20% chance to raise the user‘s Attack by 1.";
pchar Astonish_desc[] = _"30% chance to flinch the target.";
pchar Weather_Ball_desc[] = _"Power doubles and type varies in each weather.";
pchar Aromatherapy_desc[] = _"Cures the user‘s party of all status conditions.";
pchar Fake_Tears_desc[] = _"Lowers the target‘s Sp. Def by 2.";
pchar Air_Cutter_desc[] = _"High critical hit ratio. Hits adjacent foes.";
pchar Overheat_desc[] = _"Lowers the user‘s Sp. Atk by 2.";
pchar Odor_Sleuth_desc[] = _"Fighting Normal hit Ghost. Evasiveness ignored.";
pchar Rock_Tomb_desc[] = _"100% chance to lower the target‘s Speed by 1.";
pchar Silver_Wind_desc[] = _"10% chance to raise all stats by 1 (not acc/eva).";
pchar Metal_Sound_desc[] = _"Lowers the target‘s Sp. Def by 2.";
pchar Grass_Whistle_desc[] = _"Puts the target to sleep.";
pchar Tickle_desc[] = _"Lowers the target‘s Attack and Defense by 1.";
pchar Cosmic_Power_desc[] = _"Raises the user‘s Defense and Sp. Def by 1.";
pchar Water_Spout_desc[] = _"Less power as user‘s HP decreases. Hits foe(s).";
pchar Signal_Beam_desc[] = _"10% chance to confuse the target.";
pchar Shadow_Punch_desc[] = _"This move does not check accuracy.";
pchar Extrasensory_desc[] = _"10% chance to flinch the target.";
pchar Sky_Uppercut_desc[] = _"Can hit Pokemon using Bounce Fly or Sky Drop.";
pchar Sand_Tomb_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Sheer_Cold_desc[] = _"OHKOs non-Ice targets. Fails if user‘s lower level.";
pchar Muddy_Water_desc[] = _"30% chance to lower the foe(s) accuracy by 1.";
pchar Bullet_Seed_desc[] = _"Hits 2-5 times in one turn.";
pchar Aerial_Ace_desc[] = _"This move does not check accuracy.";
pchar Icicle_Spear_desc[] = _"Hits 2-5 times in one turn.";
pchar Iron_Defense_desc[] = _"Raises the user‘s Defense by 2.";
pchar Block_desc[] = _"The target cannot switch out.";
pchar Howl_desc[] = _"Raises the user‘s Attack by 1.";
pchar Dragon_Claw_desc[] = _"No additional effect.";
pchar Frenzy_Plant_desc[] = _"User cannot move next turn.";
pchar Bulk_Up_desc[] = _"Raises the user‘s Attack and Defense by 1.";
pchar Bounce_desc[] = _"Bounces turn 1. Hits turn 2. 30% paralyze.";
pchar Mud_Shot_desc[] = _"100% chance to lower the target‘s Speed by 1.";
pchar Poison_Tail_desc[] = _"High critical hit ratio. 10% chance to poison.";
pchar Covet_desc[] = _"If the user has no item it steals the target‘s.";
pchar Volt_Tackle_desc[] = _"Has 33% recoil. 10% chance to paralyze target.";
pchar Magical_Leaf_desc[] = _"This move does not check accuracy.";
pchar Water_Sport_desc[] = _"For 5 turns Fire-type attacks have 1/3 power.";
pchar Calm_Mind_desc[] = _"Raises the user‘s Sp. Atk and Sp. Def by 1.";
pchar Leaf_Blade_desc[] = _"High critical hit ratio.";
pchar Dragon_Dance_desc[] = _"Raises the user‘s Attack and Speed by 1.";
pchar Rock_Blast_desc[] = _"Hits 2-5 times in one turn.";
pchar Shock_Wave_desc[] = _"This move does not check accuracy.";
pchar Water_Pulse_desc[] = _"20% chance to confuse the target.";
pchar Doom_Desire_desc[] = _"Hits two turns after being used.";
pchar Psycho_Boost_desc[] = _"Lowers the user‘s Sp. Atk by 2.";
pchar Roost_desc[] = _"Heals 50% HP. Flying-type removed ‘til turn ends.";
pchar Gravity_desc[] = _"For 5 turns negates all Ground immunities.";
pchar Miracle_Eye_desc[] = _"Psychic hits Dark. Evasiveness ignored.";
pchar Wake_Up_Slap_desc[] = _"Power doubles if target is asleep and wakes it.";
pchar Hammer_Arm_desc[] = _"Lowers the user‘s Speed by 1.";
pchar Gyro_Ball_desc[] = _"More power the slower the user than the target.";
pchar Healing_Wish_desc[] = _"User faints. Replacement is fully healed.";
pchar Brine_desc[] = _"Power doubles if the target‘s HP is 50% or less.";
pchar Natural_Gift_desc[] = _"Power and type depends on the user‘s Berry.";
pchar Feint_desc[] = _"Nullifies Detect Protect and Quick/Wide Guard.";
pchar Pluck_desc[] = _"User steals and eats the target‘s Berry.";
pchar Tailwind_desc[] = _"For 4 turns allies‘ Speed is doubled.";
pchar Acupressure_desc[] = _"Raises a random stat of the user or an ally by 2.";
pchar Metal_Burst_desc[] = _"If hit by an attack returns 1.5x damage.";
pchar U_turn_desc[] = _"User switches out after damaging the target.";
pchar Close_Combat_desc[] = _"Lowers the user‘s Defense and Sp. Def by 1.";
pchar Payback_desc[] = _"Power doubles if the user moves after the target.";
pchar Assurance_desc[] = _"Power doubles if target was damaged this turn.";
pchar Embargo_desc[] = _"For 5 turns the target can‘t use any items.";
pchar Fling_desc[] = _"Flings the user‘s item at the target. Power varies.";
pchar Psycho_Shift_desc[] = _"Transfers the user‘s status ailment to the target.";
pchar Trump_Card_desc[] = _"More power the fewer PP this move has left.";
pchar Heal_Block_desc[] = _"For 5 turns the foe(s) is prevented from healing.";
pchar Wring_Out_desc[] = _"More power the more HP the target has left.";
pchar Power_Trick_desc[] = _"Switches user‘s Attack and Defense stats.";
pchar Gastro_Acid_desc[] = _"Nullifies the target‘s Ability.";
pchar Lucky_Chant_desc[] = _"For 5 turns shields user‘s party from critical hits.";
pchar Me_First_desc[] = _"Copies a foe at 1.5x power. User must be faster.";
pchar Copycat_desc[] = _"Uses the last move used in the battle.";
pchar Power_Swap_desc[] = _"Swaps Attack and Sp. Atk stat stages with target.";
pchar Guard_Swap_desc[] = _"Swaps Defense and Sp. Def changes with target.";
pchar Punishment_desc[] = _"60 power +20 for each of the target‘s stat boosts.";
pchar Last_Resort_desc[] = _"Fails unless each known move has been used.";
pchar Worry_Seed_desc[] = _"The target‘s Ability becomes Insomnia.";
pchar Sucker_Punch_desc[] = _"Usually goes first. Fails if target is not attacking.";
pchar Toxic_Spikes_desc[] = _"Poisons grounded foes on switch-in. Max 2 layers.";
pchar Heart_Swap_desc[] = _"Swaps all stat changes with target.";
pchar Aqua_Ring_desc[] = _"User recovers 1/16 max HP per turn.";
pchar Magnet_Rise_desc[] = _"For 5 turns the user is immune to Ground moves.";
pchar Flare_Blitz_desc[] = _"Has 33% recoil. 10% chance to burn. Thaws user.";
pchar Force_Palm_desc[] = _"30% chance to paralyze the target.";
pchar Aura_Sphere_desc[] = _"This move does not check accuracy.";
pchar Rock_Polish_desc[] = _"Raises the user‘s Speed by 2.";
pchar Poison_Jab_desc[] = _"30% chance to poison the target.";
pchar Dark_Pulse_desc[] = _"20% chance to flinch the target.";
pchar Night_Slash_desc[] = _"High critical hit ratio.";
pchar Aqua_Tail_desc[] = _"No additional effect.";
pchar Seed_Bomb_desc[] = _"No additional effect.";
pchar Air_Slash_desc[] = _"30% chance to flinch the target.";
pchar X_Scissor_desc[] = _"No additional effect.";
pchar Bug_Buzz_desc[] = _"10% chance to lower the target‘s Sp. Def. by 1.";
pchar Dragon_Pulse_desc[] = _"No additional effect.";
pchar Dragon_Rush_desc[] = _"20% chance to flinch the target.";
pchar Power_Gem_desc[] = _"No additional effect.";
pchar Drain_Punch_desc[] = _"User recovers 50% of the damage dealt.";
pchar Vacuum_Wave_desc[] = _"Usually goes first.";
pchar Focus_Blast_desc[] = _"10% chance to lower the target‘s Sp. Def by 1.";
pchar Energy_Ball_desc[] = _"10% chance to lower the target‘s Sp. Def. by 1.";
pchar Brave_Bird_desc[] = _"Has 33% recoil.";
pchar Earth_Power_desc[] = _"10% chance to lower the target‘s Sp. Def. by 1.";
pchar Switcheroo_desc[] = _"User switches its held item with the target‘s.";
pchar Giga_Impact_desc[] = _"User cannot move next turn.";
pchar Nasty_Plot_desc[] = _"Raises the user‘s Sp. Atk by 2.";
pchar Bullet_Punch_desc[] = _"Usually goes first.";
pchar Avalanche_desc[] = _"Power doubles if user is damaged by the target.";
pchar Ice_Shard_desc[] = _"Usually goes first.";
pchar Shadow_Claw_desc[] = _"High critical hit ratio.";
pchar Thunder_Fang_desc[] = _"10% chance to paralyze. 10% chance to flinch.";
pchar Ice_Fang_desc[] = _"10% chance to freeze. 10% chance to flinch.";
pchar Fire_Fang_desc[] = _"10% chance to burn. 10% chance to flinch.";
pchar Shadow_Sneak_desc[] = _"Usually goes first.";
pchar Mud_Bomb_desc[] = _"30% chance to lower the target‘s accuracy by 1.";
pchar Psycho_Cut_desc[] = _"High critical hit ratio.";
pchar Zen_Headbutt_desc[] = _"20% chance to flinch the target.";
pchar Mirror_Shot_desc[] = _"30% chance to lower the target‘s accuracy by 1.";
pchar Flash_Cannon_desc[] = _"10% chance to lower the target‘s Sp. Def by 1.";
pchar Rock_Climb_desc[] = _"20% chance to confuse the target.";
pchar Defog_desc[] = _"-1 evasion- clears user and target side‘s hazards.";
pchar Trick_Room_desc[] = _"For 5 turns slower Pokemon move first.";
pchar Draco_Meteor_desc[] = _"Lowers the user‘s Sp. Atk by 2.";
pchar Discharge_desc[] = _"30% chance to paralyze adjacent Pokemon.";
pchar Lava_Plume_desc[] = _"30% chance to burn adjacent Pokemon.";
pchar Leaf_Storm_desc[] = _"Lowers the user‘s Sp. Atk by 2.";
pchar Power_Whip_desc[] = _"No additional effect.";
pchar Rock_Wrecker_desc[] = _"User cannot move next turn.";
pchar Cross_Poison_desc[] = _"High critical hit ratio. 10% chance to poison.";
pchar Gunk_Shot_desc[] = _"30% chance to poison the target.";
pchar Iron_Head_desc[] = _"30% chance to flinch the target.";
pchar Magnet_Bomb_desc[] = _"This move does not check accuracy.";
pchar Stone_Edge_desc[] = _"High critical hit ratio.";
pchar Captivate_desc[] = _"Lowers the foe(s) Sp. Atk by 2 if opposite gender.";
pchar Stealth_Rock_desc[] = _"Hurts foes on switch-in. Factors Rock weakness.";
pchar Grass_Knot_desc[] = _"More power the heavier the target.";
pchar Chatter_desc[] = _"100% chance to confuse the target.";
pchar Judgment_desc[] = _"Type varies based on the held Plate.";
pchar Bug_Bite_desc[] = _"User steals and eats the target‘s Berry.";
pchar Charge_Beam_desc[] = _"70% chance to raise the user‘s Sp. Atk by 1.";
pchar Wood_Hammer_desc[] = _"Has 33% recoil.";
pchar Aqua_Jet_desc[] = _"Usually goes first.";
pchar Attack_Order_desc[] = _"High critical hit ratio.";
pchar Defend_Order_desc[] = _"Raises the user‘s Defense and Sp. Def by 1.";
pchar Heal_Order_desc[] = _"Heals the user by 50% of its max HP.";
pchar Head_Smash_desc[] = _"Has 1/2 recoil.";
pchar Double_Hit_desc[] = _"Hits 2 times in one turn.";
pchar Roar_of_Time_desc[] = _"User cannot move next turn.";
pchar Spacial_Rend_desc[] = _"High critical hit ratio.";
pchar Lunar_Dance_desc[] = _"User faints. Replacement is fully healed with PP.";
pchar Crush_Grip_desc[] = _"More power the more HP the target has left.";
pchar Magma_Storm_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Dark_Void_desc[] = _"Puts the foe(s) to sleep.";
pchar Seed_Flare_desc[] = _"40% chance to lower the target‘s Sp. Def by 2.";
pchar Ominous_Wind_desc[] = _"10% chance to raise all stats by 1 (not acc/eva).";
pchar Shadow_Force_desc[] = _"Disappears turn 1. Hits turn 2. Breaks protection.";
pchar Hone_Claws_desc[] = _"Raises the user‘s Attack and accuracy by 1.";
pchar Wide_Guard_desc[] = _"Protects allies from multi-target moves this turn.";
pchar Guard_Split_desc[] = _"Averages Defense and Sp. Def stats with target.";
pchar Power_Split_desc[] = _"Averages Attack and Sp. Atk stats with target.";
pchar Wonder_Room_desc[] = _"For 5 turns all Defense and Sp. Def stats switch.";
pchar Psyshock_desc[] = _"Damages target based on Defense not Sp. Def.";
pchar Venoshock_desc[] = _"Power doubles if the target is poisoned.";
pchar Autotomize_desc[] = _"Raises the user‘s Speed by 2- user loses 100 kg.";
pchar Rage_Powder_desc[] = _"The foes‘ moves target the user on the turn used.";
pchar Telekinesis_desc[] = _"For 3 turns target floats but moves can‘t miss it.";
pchar Magic_Room_desc[] = _"For 5 turns all held items have no effect.";
pchar Smack_Down_desc[] = _"Removes the target‘s Ground immunity.";
pchar Storm_Throw_desc[] = _"Always results in a critical hit.";
pchar Flame_Burst_desc[] = _"Damages Pokemon next to the target as well.";
pchar Sludge_Wave_desc[] = _"10% chance to poison adjacent Pokemon.";
pchar Quiver_Dance_desc[] = _"Raises the user‘s Sp. Atk Sp. Def Speed by 1.";
pchar Heavy_Slam_desc[] = _"More power the heavier the user than the target.";
pchar Synchronoise_desc[] = _"Hits adjacent Pokemon sharing the user‘s type.";
pchar Electro_Ball_desc[] = _"More power the faster the user is than the target.";
pchar Soak_desc[] = _"Changes the target‘s type to Water.";
pchar Flame_Charge_desc[] = _"100% chance to raise the user‘s Speed by 1.";
pchar Coil_desc[] = _"Raises user‘s Attack Defense and accuracy by 1.";
pchar Low_Sweep_desc[] = _"100% chance to lower the target‘s Speed by 1.";
pchar Acid_Spray_desc[] = _"100% chance to lower the target‘s Sp. Def by 2.";
pchar Foul_Play_desc[] = _"Uses target‘s Attack stat in damage calculation.";
pchar Simple_Beam_desc[] = _"The target‘s Ability becomes Simple.";
pchar Entrainment_desc[] = _"The target‘s Ability changes to match the user‘s.";
pchar After_You_desc[] = _"The target makes its move right after the user.";
pchar Round_desc[] = _"Power doubles if others used Round this turn.";
pchar Echoed_Voice_desc[] = _"Power increases when used on consecutive turns.";
pchar Chip_Away_desc[] = _"Ignores the target‘s stat stage changes.";
pchar Clear_Smog_desc[] = _"Eliminates the target‘s stat changes.";
pchar Stored_Power_desc[] = _" + 20 power for each of the user‘s stat boosts.";
pchar Quick_Guard_desc[] = _"Protects allies from priority attacks this turn.";
pchar Ally_Switch_desc[] = _"The user swaps positions with its ally.";
pchar Scald_desc[] = _"30% chance to burn the target. Thaws target.";
pchar Shell_Smash_desc[] = _"Lowers Def SpD by 1- raises Atk SpA Spe by 2.";
pchar Heal_Pulse_desc[] = _"Heals the target by 50% of its max HP.";
pchar Hex_desc[] = _"Power doubles if the target has a status ailment.";
pchar Sky_Drop_desc[] = _"User and foe fly up turn 1. Damages on turn 2.";
pchar Shift_Gear_desc[] = _"Raises the user‘s Speed by 2 and Attack by 1.";
pchar Circle_Throw_desc[] = _"Forces the target to switch to a random ally.";
pchar Incinerate_desc[] = _"Destroys the foe(s) Berry/Gem.";
pchar Quash_desc[] = _"Forces the target to move last this turn.";
pchar Acrobatics_desc[] = _"Power doubles if the user has no held item.";
pchar Reflect_Type_desc[] = _"User becomes the same type as the target.";
pchar Retaliate_desc[] = _"Power doubles if an ally fainted last turn.";
pchar Final_Gambit_desc[] = _"Does damage equal to the user‘s HP. User faints.";
pchar Bestow_desc[] = _"User passes its held item to the target.";
pchar Inferno_desc[] = _"100% chance to burn the target.";
pchar Water_Pledge_desc[] = _"Use with Grass or Fire Pledge for added effect.";
pchar Fire_Pledge_desc[] = _"Use with Grass or Water Pledge for added effect.";
pchar Grass_Pledge_desc[] = _"Use with Fire or Water Pledge for added effect.";
pchar Volt_Switch_desc[] = _"User switches out after damaging the target.";
pchar Struggle_Bug_desc[] = _"100% chance to lower the foe(s) Sp. Atk by 1.";
pchar Bulldoze_desc[] = _"100% chance to lower adjacent Pkmn Speed by 1.";
pchar Frost_Breath_desc[] = _"Always results in a critical hit.";
pchar Dragon_Tail_desc[] = _"Forces the target to switch to a random ally.";
pchar Work_Up_desc[] = _"Raises the user‘s Attack and Sp. Atk by 1.";
pchar Electroweb_desc[] = _"100% chance to lower the foe(s) Speed by 1.";
pchar Wild_Charge_desc[] = _"Has 1/4 recoil.";
pchar Drill_Run_desc[] = _"High critical hit ratio.";
pchar Dual_Chop_desc[] = _"Hits 2 times in one turn.";
pchar Heart_Stamp_desc[] = _"30% chance to flinch the target.";
pchar Horn_Leech_desc[] = _"User recovers 50% of the damage dealt.";
pchar Sacred_Sword_desc[] = _"Ignores the target‘s stat stage changes.";
pchar Razor_Shell_desc[] = _"50% chance to lower the target‘s Defense by 1.";
pchar Heat_Crash_desc[] = _"More power the heavier the user than the target.";
pchar Leaf_Tornado_desc[] = _"50% chance to lower the target‘s accuracy by 1.";
pchar Steamroller_desc[] = _"30% chance to flinch the target.";
pchar Cotton_Guard_desc[] = _"Raises the user‘s Defense by 3.";
pchar Night_Daze_desc[] = _"40% chance to lower the target‘s accuracy by 1.";
pchar Psystrike_desc[] = _"Damages target based on Defense not Sp. Def.";
pchar Tail_Slap_desc[] = _"Hits 2-5 times in one turn.";
pchar Hurricane_desc[] = _"30% chance to confuse target. Can‘t miss in rain.";
pchar Head_Charge_desc[] = _"Has 1/4 recoil.";
pchar Gear_Grind_desc[] = _"Hits 2 times in one turn.";
pchar Searing_Shot_desc[] = _"30% chance to burn adjacent Pokemon.";
pchar Techno_Blast_desc[] = _"Type varies based on the held Drive.";
pchar Relic_Song_desc[] = _"10% chance to sleep foe(s). Meloetta transforms.";
pchar Secret_Sword_desc[] = _"Damages target based on Defense not Sp. Def.";
pchar Glaciate_desc[] = _"100% chance to lower the foe(s) Speed by 1.";
pchar Bolt_Strike_desc[] = _"20% chance to paralyze the target.";
pchar Blue_Flare_desc[] = _"20% chance to burn the target.";
pchar Fiery_Dance_desc[] = _"50% chance to raise the user‘s Sp. Atk by 1.";
pchar Freeze_Shock_desc[] = _"Charges turn 1. Hits turn 2. 30% paralyze.";
pchar Ice_Burn_desc[] = _"Charges turn 1. Hits turn 2. 30% burn.";
pchar Snarl_desc[] = _"100% chance to lower the foe(s) Sp. Atk by 1.";
pchar Icicle_Crash_desc[] = _"30% chance to flinch the target.";
pchar V_create_desc[] = _"Lowers the user‘s Defense Sp. Def Speed by 1.";
pchar Fusion_Flare_desc[] = _"Power doubles if used after Fusion Bolt.";
pchar Fusion_Bolt_desc[] = _"Power doubles if used after Fusion Flare.";
pchar Flying_Press_desc[] = _"Combines Flying in its type effectiveness.";
pchar Mat_Block_desc[] = _"Protects allies from attacks. First turn out only.";
pchar Belch_desc[] = _"Cannot be selected until the user eats a Berry.";
pchar Rototiller_desc[] = _"Raises Atk Sp. Atk of grounded Grass types by 1.";
pchar Sticky_Web_desc[] = _"Lowers Speed of grounded foes by 1 on switch-in.";
pchar Fell_Stinger_desc[] = _"Raises user‘s Attack by 3 if this KOes the target.";
pchar Phantom_Force_desc[] = _"Disappears turn 1. Hits turn 2. Breaks protection.";
pchar Trick_or_Treat_desc[] = _"Adds Ghost to the target‘s type(s).";
pchar Noble_Roar_desc[] = _"Lowers the target‘s Attack and Sp. Atk by 1.";
pchar Ion_Deluge_desc[] = _"Normal moves become Electric type this turn.";
pchar Parabolic_Charge_desc[] = _"User recovers 50% of the damage dealt.";
pchar Forests_Curse_desc[] = _"Adds Grass to the target‘s type(s).";
pchar Petal_Blizzard_desc[] = _"No additional effect. Hits adjacent Pokemon.";
pchar Freeze_Dry_desc[] = _"10% chance to freeze. Super effective on Water.";
pchar Disarming_Voice_desc[] = _"This move does not check accuracy. Hits foes.";
pchar Parting_Shot_desc[] = _"Lowers target‘s Atk Sp. Atk by 1. User switches.";
pchar Topsy_Turvy_desc[] = _"Inverts the target‘s stat stages.";
pchar Draining_Kiss_desc[] = _"User recovers 75% of the damage dealt.";
pchar Crafty_Shield_desc[] = _"Protects allies from Status moves this turn.";
pchar Flower_Shield_desc[] = _"Raises Defense by 1 of all active Grass types.";
pchar Grassy_Terrain_desc[] = _"5 turns. Grounded: +Grass power+1/16 max HP.";
pchar Misty_Terrain_desc[] = _"5 turns. Can‘t status-Dragon power vs grounded.";
pchar Electrify_desc[] = _"Changes the target‘s move to Electric this turn.";
pchar Play_Rough_desc[] = _"10% chance to lower the target‘s Attack by 1.";
pchar Fairy_Wind_desc[] = _"No additional effect.";
pchar Moonblast_desc[] = _"30% chance to lower the target‘s Sp. Atk by 1.";
pchar Boomburst_desc[] = _"No additional effect. Hits adjacent Pokemon.";
pchar Fairy_Lock_desc[] = _"Prevents all Pokemon from switching next turn.";
pchar Kings_Shield_desc[] = _"Protects from attacks. Contact: lowers Atk by 2.";
pchar Play_Nice_desc[] = _"Lowers the target‘s Attack by 1.";
pchar Confide_desc[] = _"Lowers the target‘s Sp. Atk by 1.";
pchar Diamond_Storm_desc[] = _"50% chance to raise user‘s Def by 2 for each hit.";
pchar Steam_Eruption_desc[] = _"30% chance to burn the target.";
pchar Hyperspace_Hole_desc[] = _"Breaks the target‘s protection for this turn.";
pchar Water_Shuriken_desc[] = _"Hits 2-5 times in one turn.";
pchar Mystical_Fire_desc[] = _"100% chance to lower the target‘s Sp. Atk by 1.";
pchar Spiky_Shield_desc[] = _"Protects from moves. Contact: loses 1/8 max HP.";
pchar Aromatic_Mist_desc[] = _"Raises an ally‘s Sp. Def by 1.";
pchar Eerie_Impulse_desc[] = _"Lowers the target‘s Sp. Atk by 2.";
pchar Venom_Drench_desc[] = _"Lowers Atk Sp. Atk Speed of poisoned foes by 1.";
pchar Powder_desc[] = _"If using a Fire move target loses 1/4 max HP.";
pchar Geomancy_desc[] = _"Charges then raises SpA SpD Spe by 2 turn 2.";
pchar Magnetic_Flux_desc[] = _"Raises Def Sp. Def of allies with Plus/Minus by 1.";
pchar Happy_Hour_desc[] = _"No competitive use.";
pchar Electric_Terrain_desc[] = _"5 turns. Grounded: +Electric power can‘t sleep.";
pchar Dazzling_Gleam_desc[] = _"No additional effect. Hits adjacent foes.";
pchar Celebrate_desc[] = _"No competitive use. Or any use.";
pchar Baby_Doll_Eyes_desc[] = _"Lowers the target‘s Attack by 1.";
pchar Nuzzle_desc[] = _"100% chance to paralyze the target.";
pchar Hold_Back_desc[] = _"Always leaves the target with at least 1 HP.";
pchar Infestation_desc[] = _"Traps and damages the target for 4-5 turns.";
pchar Power_Up_Punch_desc[] = _"100% chance to raise the user‘s Attack by 1.";
pchar Oblivion_Wing_desc[] = _"User recovers 75% of the damage dealt.";
pchar Thousand_Arrows_desc[] = _"Grounds adjacent foes. First hit neutral on Flying.";
pchar Thousand_Waves_desc[] = _"Hits adjacent foes. Prevents them from switching.";
pchar Hold_Hands_desc[] = _"No competitive use. Or any use.";
pchar Lands_Wrath_desc[] = _"No additional effect. Hits adjacent foes.";
pchar Light_of_Ruin_desc[] = _"Has 1/2 recoil.";
pchar Origin_Pulse_desc[] = _"No additional effect. Hits adjacent foes.";
pchar Precipice_Blades_desc[] = _"No additional effect. Hits adjacent Pokemon.";
pchar Dragon_Ascent_desc[] = _"Lowers the user‘s Defense and Sp. Def by 1.";
pchar Hyperspace_Fury_desc[] = _"Hoopa-U: Lowers user‘s Def by 1- breaks protection.";
pchar Shore_Up_desc[] = _"Heals the user by a weather-dependent amount.";
pchar First_Impression_desc[] = _"Hits first. First turn out only.";
pchar Baneful_Bunker_desc[] = _"Protects from moves. Contact: poison.";
pchar Spirit_Shackle_desc[] = _"Prevents the target from switching out.";
pchar Darkest_Lariat_desc[] = _"Ignores the target‘s stat stage changes.";
pchar Sparkling_Aria_desc[] = _"The target is cured of its burn.";
pchar Ice_Hammer_desc[] = _"Lowers the user‘s Speed by 1.";
pchar Floral_Healing_desc[] = _"Heals the target by 50% of its max HP.";
pchar High_Horsepower_desc[] = _"No additional effect.";
pchar Strength_Sap_desc[] = _"User heals HP=target‘s Atk stat. Lowers Atk by 1.";
pchar Solar_Blade_desc[] = _"Charges turn 1. Hits turn 2. No charge in sunlight.";
pchar Leafage_desc[] = _"No additional effect.";
pchar Spotlight_desc[] = _"Moves redirect to the target on the turn used.";
pchar Toxic_Thread_desc[] = _"Lowers the target‘s Speed by 1 and poisons it.";
pchar Laser_Focus_desc[] = _"Next turn the user‘s attack will be a critical hit.";
pchar Gear_Up_desc[] = _"Raises Atk Sp. Atk of allies with Plus/Minus by 1.";
pchar Throat_Chop_desc[] = _"For 2 turns the target cannot use sound moves.";
pchar Pollen_Puff_desc[] = _"If the target is an ally heals 50% of its max HP.";
pchar Anchor_Shot_desc[] = _"Prevents the target from switching out.";
pchar Psychic_Terrain_desc[] = _"5 turns. Grounded: +Psychic power priority-safe.";
pchar Lunge_desc[] = _"100% chance to lower the target‘s Attack by 1.";
pchar Fire_Lash_desc[] = _"100% chance to lower the target‘s Defense by 1.";
pchar Power_Trip_desc[] = _" + 20 power for each of the user‘s stat boosts.";
pchar Burn_Up_desc[] = _"User‘s Fire-type is removed until it switches out.";
pchar Speed_Swap_desc[] = _"Swaps Speed stat with target.";
pchar Smart_Strike_desc[] = _"This move does not check accuracy.";
pchar Purify_desc[] = _"Cures target‘s status- heals user 1/2 maxHP if so.";
pchar Revelation_Dance_desc[] = _"Type varies based on the user‘s primary type.";
pchar Core_Enforcer_desc[] = _"Nullifies the foe(s) Ability if the target moves first.";
pchar Trop_Kick_desc[] = _"100% chance to lower the target‘s Attack by 1.";
pchar Instruct_desc[] = _"The target immediately uses its last used move.";
pchar Beak_Blast_desc[] = _"Burns on contact with the user before it moves.";
pchar Clanging_Scales_desc[] = _"Lowers the user‘s Defense by 1.";
pchar Dragon_Hammer_desc[] = _"No additional effect.";
pchar Brutal_Swing_desc[] = _"No additional effect. Hits adjacent Pokemon.";
pchar Aurora_Veil_desc[] = _"For 5 turns damage to allies is halved. Hail only.";
pchar Shell_Trap_desc[] = _"User must take physical damage before moving.";
pchar Fleur_Cannon_desc[] = _"Lowers the user‘s Sp. Atk by 2.";
pchar Psychic_Fangs_desc[] = _"Destroys screens unless the target is immune.";
pchar Stomping_Tantrum_desc[] = _"Power doubles if the user‘s last move failed.";
pchar Shadow_Bone_desc[] = _"20% chance to lower the target‘s Defense by 1.";
pchar Accelerock_desc[] = _"Usually goes first.";
pchar Liquidation_desc[] = _"20% chance to lower the target‘s Defense by 1.";
pchar Prismatic_Laser_desc[] = _"User cannot move next turn.";
pchar Spectral_Thief_desc[] = _"Steals target‘s boosts before dealing damage.";
pchar Sunsteel_Strike_desc[] = _"Ignores the Abilities of other Pokemon.";
pchar Moongeist_Beam_desc[] = _"Ignores the Abilities of other Pokemon.";
pchar Tearful_Look_desc[] = _"Lowers the target‘s Attack and Sp. Atk by 1.";
pchar Zing_Zap_desc[] = _"30% chance to flinch the target.";
pchar Natures_Madness_desc[] = _"Does damage equal to 1/2 target‘s current HP.";
pchar Multi_Attack_desc[] = _"Type varies based on the held Memory.";




void nullsub_move(void)
{
    return;
}

struct move_callbacks null_mcb = {
};

struct move_procs no_procs = {
    0, 0, STAT_NONE, STAT_NONE, 0, 0, 1, 1
};


struct move_data move_t[] = {
    {_"-", 0, 0, (pchar*)Pound_desc, 0, 0, 0, MOVE_PHYSICAL, MTYPE_EGG, &m_flags[0], &no_procs, &null_mcb},
	{_"Pound", 100, 40, (pchar*)Pound_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[1], &no_procs, &null_mcb},
	{_"Karate Chop", 100, 50, (pchar*)Karate_Chop_desc, 25, 0, 2, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[2], &no_procs, &null_mcb},
	{_"Double Slap", 85, 15, (pchar*)Double_Slap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[3], &no_procs, &null_mcb},
	{_"Comet Punch", 85, 18, (pchar*)Comet_Punch_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[4], &no_procs, &null_mcb},
	{_"Mega Punch", 85, 80, (pchar*)Mega_Punch_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[5], &no_procs, &null_mcb},
	{_"Pay Day", 100, 40, (pchar*)Pay_Day_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[6], &no_procs, &null_mcb},
	{_"Fire Punch", 100, 75, (pchar*)Fire_Punch_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[7], &no_procs, &null_mcb},
	{_"Ice Punch", 100, 75, (pchar*)Ice_Punch_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[8], &no_procs, &null_mcb},
	{_"Thunder Punch", 100, 75, (pchar*)Thunder_Punch_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[9], &no_procs, &null_mcb},
	{_"Scratch", 100, 40, (pchar*)Scratch_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[10], &no_procs, &null_mcb},
	{_"Vice Grip", 100, 55, (pchar*)Vice_Grip_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[11], &no_procs, &null_mcb},
	{_"Guillotine", 30, 0, (pchar*)Guillotine_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[12], &no_procs, &null_mcb},
	{_"Razor Wind", 100, 80, (pchar*)Razor_Wind_desc, 10, 0, 2, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[13], &no_procs, &null_mcb},
	{_"Swords Dance", 255, 0, (pchar*)Swords_Dance_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[14], &no_procs, &null_mcb},
	{_"Cut", 95, 50, (pchar*)Cut_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[15], &no_procs, &null_mcb},
	{_"Gust", 100, 40, (pchar*)Gust_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[16], &no_procs, &null_mcb},
	{_"Wing Attack", 100, 60, (pchar*)Wing_Attack_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[17], &no_procs, &null_mcb},
	{_"Whirlwind", 255, 0, (pchar*)Whirlwind_desc, 20, -6, 1, 3, MTYPE_NORMAL, &m_flags[18], &no_procs, &null_mcb},
	{_"Fly", 95, 90, (pchar*)Fly_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[19], &no_procs, &null_mcb},
	{_"Bind", 85, 15, (pchar*)Bind_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[20], &no_procs, &null_mcb},
	{_"Slam", 75, 80, (pchar*)Slam_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[21], &no_procs, &null_mcb},
	{_"Vine Whip", 100, 45, (pchar*)Vine_Whip_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[22], &no_procs, &null_mcb},
	{_"Stomp", 100, 65, (pchar*)Stomp_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[23], &no_procs, &null_mcb},
	{_"Double Kick", 100, 30, (pchar*)Double_Kick_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[24], &no_procs, &null_mcb},
	{_"Mega Kick", 75, 120, (pchar*)Mega_Kick_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[25], &no_procs, &null_mcb},
	{_"Jump Kick", 95, 100, (pchar*)Jump_Kick_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[26], &no_procs, &null_mcb},
	{_"Rolling Kick", 85, 60, (pchar*)Rolling_Kick_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[27], &no_procs, &null_mcb},
	{_"Sand Attack", 100, 0, (pchar*)Sand_Attack_desc, 15, 0, 1, MOVE_STATUS, MTYPE_GROUND, &m_flags[28], &no_procs, &null_mcb},
	{_"Headbutt", 100, 70, (pchar*)Headbutt_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[29], &no_procs, &null_mcb},
	{_"Horn Attack", 100, 65, (pchar*)Horn_Attack_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[30], &no_procs, &null_mcb},
	{_"Fury Attack", 85, 15, (pchar*)Fury_Attack_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[31], &no_procs, &null_mcb},
	{_"Horn Drill", 30, 0, (pchar*)Horn_Drill_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[32], &no_procs, &null_mcb},
	{_"Tackle", 100, 40, (pchar*)Tackle_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[33], &no_procs, &null_mcb},
	{_"Body Slam", 100, 85, (pchar*)Body_Slam_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[34], &no_procs, &null_mcb},
	{_"Wrap", 90, 15, (pchar*)Wrap_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[35], &no_procs, &null_mcb},
	{_"Take Down", 85, 90, (pchar*)Take_Down_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[36], &no_procs, &null_mcb},
	{_"Thrash", 100, 120, (pchar*)Thrash_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[37], &no_procs, &null_mcb},
	{_"Double-Edge", 100, 120, (pchar*)Double_Edge_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[38], &no_procs, &null_mcb},
	{_"Tail Whip", 100, 0, (pchar*)Tail_Whip_desc, 30, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[39], &no_procs, &null_mcb},
	{_"Poison Sting", 100, 15, (pchar*)Poison_Sting_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[40], &no_procs, &null_mcb},
	{_"Twineedle", 100, 25, (pchar*)Twineedle_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[41], &no_procs, &null_mcb},
	{_"Pin Missile", 95, 25, (pchar*)Pin_Missile_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[42], &no_procs, &null_mcb},
	{_"Leer", 100, 0, (pchar*)Leer_desc, 30, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[43], &no_procs, &null_mcb},
	{_"Bite", 100, 60, (pchar*)Bite_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[44], &no_procs, &null_mcb},
	{_"Growl", 100, 0, (pchar*)Growl_desc, 40, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[45], &no_procs, &null_mcb},
	{_"Roar", 255, 0, (pchar*)Roar_desc, 20, -6, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[46], &no_procs, &null_mcb},
	{_"Sing", 55, 0, (pchar*)Sing_desc, 15, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[47], &no_procs, &null_mcb},
	{_"Supersonic", 55, 0, (pchar*)Supersonic_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[48], &no_procs, &null_mcb},
	{_"Sonic Boom", 90, 0, (pchar*)Sonic_Boom_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[49], &no_procs, &null_mcb},
	{_"Disable", 100, 0, (pchar*)Disable_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[50], &no_procs, &null_mcb},
	{_"Acid", 100, 40, (pchar*)Acid_desc, 30, 0, 1, MOVE_SPECIAL, MTYPE_POISON, &m_flags[51], &no_procs, &null_mcb},
	{_"Ember", 100, 40, (pchar*)Ember_desc, 25, 0, 1, MOVE_SPECIAL, MTYPE_FIRE, &m_flags[52], &no_procs, &null_mcb},
	{_"Flamethrower", 100, 90, (pchar*)Flamethrower_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_FIRE, &m_flags[53], &no_procs, &null_mcb},
	{_"Mist", 255, 0, (pchar*)Mist_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[54], &no_procs, &null_mcb},
	{_"Water Gun", 100, 40, (pchar*)Water_Gun_desc, 25, 0, 1, MOVE_SPECIAL, MTYPE_WATER, &m_flags[55], &no_procs, &null_mcb},
	{_"Hydro Pump", 80, 110, (pchar*)Hydro_Pump_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_WATER, &m_flags[56], &no_procs, &null_mcb},
	{_"Surf", 100, 90, (pchar*)Surf_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_WATER, &m_flags[57], &no_procs, &null_mcb},
	{_"Ice Beam", 100, 90, (pchar*)Ice_Beam_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_ICE, &m_flags[58], &no_procs, &null_mcb},
	{_"Blizzard", 70, 110, (pchar*)Blizzard_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_ICE, &m_flags[59], &no_procs, &null_mcb},
	{_"Psybeam", 100, 65, (pchar*)Psybeam_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_PSYCHIC, &m_flags[60], &no_procs, &null_mcb},
	{_"Bubble Beam", 100, 65, (pchar*)Bubble_Beam_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_WATER, &m_flags[61], &no_procs, &null_mcb},
	{_"Aurora Beam", 100, 65, (pchar*)Aurora_Beam_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_ICE, &m_flags[62], &no_procs, &null_mcb},
	{_"Hyper Beam", 90, 150, (pchar*)Hyper_Beam_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[63], &no_procs, &null_mcb},
	{_"Peck", 100, 35, (pchar*)Peck_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[64], &no_procs, &null_mcb},
	{_"Drill Peck", 100, 80, (pchar*)Drill_Peck_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[65], &no_procs, &null_mcb},
	{_"Submission", 80, 80, (pchar*)Submission_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[66], &no_procs, &null_mcb},
	{_"Low Kick", 100, 0, (pchar*)Low_Kick_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[67], &no_procs, &null_mcb},
	{_"Counter", 100, 0, (pchar*)Counter_desc, 20, -5, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[68], &no_procs, &null_mcb},
	{_"Seismic Toss", 100, 0, (pchar*)Seismic_Toss_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[69], &no_procs, &null_mcb},
	{_"Strength", 100, 80, (pchar*)Strength_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[70], &no_procs, &null_mcb},
	{_"Absorb", 100, 20, (pchar*)Absorb_desc, 25, 0, 1, MOVE_SPECIAL, MTYPE_GRASS, &m_flags[71], &no_procs, &null_mcb},
	{_"Mega Drain", 100, 40, (pchar*)Mega_Drain_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_GRASS, &m_flags[72], &no_procs, &null_mcb},
	{_"Leech Seed", 90, 0, (pchar*)Leech_Seed_desc, 10, 0, 1, MOVE_STATUS, MTYPE_GRASS, &m_flags[73], &no_procs, &null_mcb},
	{_"Growth", 255, 0, (pchar*)Growth_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[74], &no_procs, &null_mcb},
	{_"Razor Leaf", 95, 55, (pchar*)Razor_Leaf_desc, 25, 0, 2, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[75], &no_procs, &null_mcb},
	{_"Solar Beam", 100, 120, (pchar*)Solar_Beam_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_GRASS, &m_flags[76], &no_procs, &null_mcb},
	{_"Poison Powder", 75, 0, (pchar*)Poison_Powder_desc, 35, 0, 1, MOVE_STATUS, MTYPE_POISON, &m_flags[77], &no_procs, &null_mcb},
	{_"Stun Spore", 75, 0, (pchar*)Stun_Spore_desc, 30, 0, 1, MOVE_STATUS, MTYPE_GRASS, &m_flags[78], &no_procs, &null_mcb},
	{_"Sleep Powder", 75, 0, (pchar*)Sleep_Powder_desc, 15, 0, 1, MOVE_STATUS, MTYPE_GRASS, &m_flags[79], &no_procs, &null_mcb},
	{_"Petal Dance", 100, 120, (pchar*)Petal_Dance_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_GRASS, &m_flags[80], &no_procs, &null_mcb},
	{_"String Shot", 95, 0, (pchar*)String_Shot_desc, 40, 0, 1, MOVE_STATUS, MTYPE_BUG, &m_flags[81], &no_procs, &null_mcb},
	{_"Dragon Rage", 100, 0, (pchar*)Dragon_Rage_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_DRAGON, &m_flags[82], &no_procs, &null_mcb},
	{_"Fire Spin", 85, 35, (pchar*)Fire_Spin_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_FIRE, &m_flags[83], &no_procs, &null_mcb},
	{_"Thunder Shock", 100, 40, (pchar*)Thunder_Shock_desc, 30, 0, 1, MOVE_SPECIAL, MTYPE_ELECTRIC, &m_flags[84], &no_procs, &null_mcb},
	{_"Thunderbolt", 100, 90, (pchar*)Thunderbolt_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_ELECTRIC, &m_flags[85], &no_procs, &null_mcb},
	{_"Thunder Wave", 90, 0, (pchar*)Thunder_Wave_desc, 20, 0, 1, MOVE_STATUS, MTYPE_ELECTRIC, &m_flags[86], &no_procs, &null_mcb},
	{_"Thunder", 70, 110, (pchar*)Thunder_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_ELECTRIC, &m_flags[87], &no_procs, &null_mcb},
	{_"Rock Throw", 90, 50, (pchar*)Rock_Throw_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[88], &no_procs, &null_mcb},
	{_"Earthquake", 100, 100, (pchar*)Earthquake_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[89], &no_procs, &null_mcb},
	{_"Fissure", 30, 0, (pchar*)Fissure_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[90], &no_procs, &null_mcb},
	{_"Dig", 100, 80, (pchar*)Dig_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[91], &no_procs, &null_mcb},
	{_"Toxic", 90, 0, (pchar*)Toxic_desc, 10, 0, 1, MOVE_STATUS, MTYPE_POISON, &m_flags[92], &no_procs, &null_mcb},
	{_"Confusion", 100, 50, (pchar*)Confusion_desc, 25, 0, 1, MOVE_SPECIAL, MTYPE_PSYCHIC, &m_flags[93], &no_procs, &null_mcb},
	{_"Psychic", 100, 90, (pchar*)Psychic_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_PSYCHIC, &m_flags[94], &no_procs, &null_mcb},
	{_"Hypnosis", 60, 0, (pchar*)Hypnosis_desc, 20, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[95], &no_procs, &null_mcb},
	{_"Meditate", 255, 0, (pchar*)Meditate_desc, 40, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[96], &no_procs, &null_mcb},
	{_"Agility", 255, 0, (pchar*)Agility_desc, 30, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[97], &no_procs, &null_mcb},
	{_"Quick Attack", 100, 40, (pchar*)Quick_Attack_desc, 30, 1, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[98], &no_procs, &null_mcb},
	{_"Rage", 100, 20, (pchar*)Rage_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[99], &no_procs, &null_mcb},
	{_"Teleport", 255, 0, (pchar*)Teleport_desc, 20, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[100], &no_procs, &null_mcb},
	{_"Night Shade", 100, 0, (pchar*)Night_Shade_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_GHOST, &m_flags[101], &no_procs, &null_mcb},
	{_"Mimic", 255, 0, (pchar*)Mimic_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[102], &no_procs, &null_mcb},
	{_"Screech", 85, 0, (pchar*)Screech_desc, 40, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[103], &no_procs, &null_mcb},
	{_"Double Team", 255, 0, (pchar*)Double_Team_desc, 15, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[104], &no_procs, &null_mcb},
	{_"Recover", 255, 0, (pchar*)Recover_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[105], &no_procs, &null_mcb},
	{_"Harden", 255, 0, (pchar*)Harden_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[106], &no_procs, &null_mcb},
	{_"Minimize", 255, 0, (pchar*)Minimize_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[107], &no_procs, &null_mcb},
	{_"Smokescreen", 100, 0, (pchar*)Smokescreen_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[108], &no_procs, &null_mcb},
	{_"Confuse Ray", 100, 0, (pchar*)Confuse_Ray_desc, 10, 0, 1, MOVE_STATUS, MTYPE_GHOST, &m_flags[109], &no_procs, &null_mcb},
	{_"Withdraw", 255, 0, (pchar*)Withdraw_desc, 40, 0, 1, MOVE_STATUS, MTYPE_WATER, &m_flags[110], &no_procs, &null_mcb},
	{_"Defense Curl", 255, 0, (pchar*)Defense_Curl_desc, 40, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[111], &no_procs, &null_mcb},
	{_"Barrier", 255, 0, (pchar*)Barrier_desc, 20, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[112], &no_procs, &null_mcb},
	{_"Light Screen", 255, 0, (pchar*)Light_Screen_desc, 30, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[113], &no_procs, &null_mcb},
	{_"Haze", 255, 0, (pchar*)Haze_desc, 30, 0, 1, MOVE_STATUS, MTYPE_ICE, &m_flags[114], &no_procs, &null_mcb},
	{_"Reflect", 255, 0, (pchar*)Reflect_desc, 20, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[115], &no_procs, &null_mcb},
	{_"Focus Energy", 255, 0, (pchar*)Focus_Energy_desc, 30, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[116], &no_procs, &null_mcb},
	{_"Bide", 255, 0, (pchar*)Bide_desc, 10, 1, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[117], &no_procs, &null_mcb},
	{_"Metronome", 255, 0, (pchar*)Metronome_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[118], &no_procs, &null_mcb},
	{_"Mirror Move", 255, 0, (pchar*)Mirror_Move_desc, 20, 0, 1, MOVE_STATUS, MTYPE_FLYING, &m_flags[119], &no_procs, &null_mcb},
	{_"Self-Destruct", 100, 200, (pchar*)Self_Destruct_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[120], &no_procs, &null_mcb},
	{_"Egg Bomb", 75, 100, (pchar*)Egg_Bomb_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[121], &no_procs, &null_mcb},
	{_"Lick", 100, 30, (pchar*)Lick_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[122], &no_procs, &null_mcb},
	{_"Smog", 70, 30, (pchar*)Smog_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_POISON, &m_flags[123], &no_procs, &null_mcb},
	{_"Sludge", 100, 65, (pchar*)Sludge_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_POISON, &m_flags[124], &no_procs, &null_mcb},
	{_"Bone Club", 85, 65, (pchar*)Bone_Club_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[125], &no_procs, &null_mcb},
	{_"Fire Blast", 85, 110, (pchar*)Fire_Blast_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_FIRE, &m_flags[126], &no_procs, &null_mcb},
	{_"Waterfall", 100, 80, (pchar*)Waterfall_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[127], &no_procs, &null_mcb},
	{_"Clamp", 85, 35, (pchar*)Clamp_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[128], &no_procs, &null_mcb},
	{_"Swift", 255, 60, (pchar*)Swift_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[129], &no_procs, &null_mcb},
	{_"Skull Bash", 100, 130, (pchar*)Skull_Bash_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[130], &no_procs, &null_mcb},
	{_"Spike Cannon", 100, 20, (pchar*)Spike_Cannon_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[131], &no_procs, &null_mcb},
	{_"Constrict", 100, 10, (pchar*)Constrict_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[132], &no_procs, &null_mcb},
	{_"Amnesia", 255, 0, (pchar*)Amnesia_desc, 20, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[133], &no_procs, &null_mcb},
	{_"Kinesis", 80, 0, (pchar*)Kinesis_desc, 15, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[134], &no_procs, &null_mcb},
	{_"Soft-Boiled", 255, 0, (pchar*)Soft_Boiled_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[135], &no_procs, &null_mcb},
	{_"High Jump Kick", 90, 130, (pchar*)High_Jump_Kick_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[136], &no_procs, &null_mcb},
	{_"Glare", 100, 0, (pchar*)Glare_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[137], &no_procs, &null_mcb},
	{_"Dream Eater", 100, 100, (pchar*)Dream_Eater_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_PSYCHIC, &m_flags[138], &no_procs, &null_mcb},
	{_"Poison Gas", 90, 0, (pchar*)Poison_Gas_desc, 40, 0, 1, MOVE_SPECIAL, MTYPE_POISON, &m_flags[139], &no_procs, &null_mcb},
	{_"Barrage", 85, 15, (pchar*)Barrage_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[140], &no_procs, &null_mcb},
	{_"Leech Life", 100, 80, (pchar*)Leech_Life_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[141], &no_procs, &null_mcb},
	{_"Lovely Kiss", 75, 0, (pchar*)Lovely_Kiss_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[142], &no_procs, &null_mcb},
	{_"Sky Attack", 90, 140, (pchar*)Sky_Attack_desc, 5, 0, 2, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[143], &no_procs, &null_mcb},
	{_"Transform", 255, 0, (pchar*)Transform_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[144], &no_procs, &null_mcb},
	{_"Bubble", 100, 40, (pchar*)Bubble_desc, 30, 0, 1, MOVE_SPECIAL, MTYPE_WATER, &m_flags[145], &no_procs, &null_mcb},
	{_"Dizzy Punch", 100, 70, (pchar*)Dizzy_Punch_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[146], &no_procs, &null_mcb},
	{_"Spore", 100, 0, (pchar*)Spore_desc, 15, 0, 1, MOVE_STATUS, MTYPE_GRASS, &m_flags[147], &no_procs, &null_mcb},
	{_"Flash", 100, 0, (pchar*)Flash_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[148], &no_procs, &null_mcb},
	{_"Psywave", 100, 0, (pchar*)Psywave_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_PSYCHIC, &m_flags[149], &no_procs, &null_mcb},
	{_"Splash", 255, 0, (pchar*)Splash_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[150], &no_procs, &null_mcb},
	{_"Acid Armor", 255, 0, (pchar*)Acid_Armor_desc, 20, 0, 1, MOVE_STATUS, MTYPE_POISON, &m_flags[151], &no_procs, &null_mcb},
	{_"Crabhammer", 90, 100, (pchar*)Crabhammer_desc, 10, 0, 2, MOVE_SPECIAL, MTYPE_WATER, &m_flags[152], &no_procs, &null_mcb},
	{_"Explosion", 100, 250, (pchar*)Explosion_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[153], &no_procs, &null_mcb},
	{_"Fury Swipes", 80, 18, (pchar*)Fury_Swipes_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[154], &no_procs, &null_mcb},
	{_"Bonemerang", 90, 50, (pchar*)Bonemerang_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[155], &no_procs, &null_mcb},
	{_"Rest", 255, 0, (pchar*)Rest_desc, 10, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[156], &no_procs, &null_mcb},
	{_"Rock Slide", 90, 75, (pchar*)Rock_Slide_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[157], &no_procs, &null_mcb},
	{_"Hyper Fang", 90, 80, (pchar*)Hyper_Fang_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[158], &no_procs, &null_mcb},
	{_"Sharpen", 255, 0, (pchar*)Sharpen_desc, 30, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[159], &no_procs, &null_mcb},
	{_"Conversion", 255, 0, (pchar*)Conversion_desc, 30, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[160], &no_procs, &null_mcb},
	{_"Tri Attack", 100, 80, (pchar*)Tri_Attack_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[161], &no_procs, &null_mcb},
	{_"Super Fang", 90, 0, (pchar*)Super_Fang_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[162], &no_procs, &null_mcb},
	{_"Slash", 100, 70, (pchar*)Slash_desc, 20, 0, 2, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[163], &no_procs, &null_mcb},
	{_"Substitute", 255, 0, (pchar*)Substitute_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[164], &no_procs, &null_mcb},
	{_"Struggle", 255, 50, (pchar*)Struggle_desc, 1, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[165], &no_procs, &null_mcb},
	{_"Sketch", 255, 0, (pchar*)Sketch_desc, 1, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[166], &no_procs, &null_mcb},
	{_"Triple Kick", 90, 10, (pchar*)Triple_Kick_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[167], &no_procs, &null_mcb},
	{_"Thief", 100, 60, (pchar*)Thief_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[168], &no_procs, &null_mcb},
	{_"Spider Web", 255, 0, (pchar*)Spider_Web_desc, 10, 0, 1, MOVE_STATUS, MTYPE_BUG, &m_flags[169], &no_procs, &null_mcb},
	{_"Mind Reader", 255, 0, (pchar*)Mind_Reader_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[170], &no_procs, &null_mcb},
	{_"Nightmare", 100, 0, (pchar*)Nightmare_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_GHOST, &m_flags[171], &no_procs, &null_mcb},
	{_"Flame Wheel", 100, 60, (pchar*)Flame_Wheel_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[172], &no_procs, &null_mcb},
	{_"Snore", 100, 50, (pchar*)Snore_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[173], &no_procs, &null_mcb},
	{_"Curse", 255, 0, (pchar*)Curse_desc, 10, 0, 1, MOVE_STATUS, MTYPE_GHOST, &m_flags[174], &no_procs, &null_mcb},
	{_"Flail", 100, 0, (pchar*)Flail_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[175], &no_procs, &null_mcb},
	{_"Conversion 2", 255, 0, (pchar*)Conversion_2_desc, 30, 0, 1, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[176], &no_procs, &null_mcb},
	{_"Aeroblast", 95, 100, (pchar*)Aeroblast_desc, 5, 0, 2, MOVE_SPECIAL, MTYPE_FLYING, &m_flags[177], &no_procs, &null_mcb},
	{_"Cotton Spore", 100, 0, (pchar*)Cotton_Spore_desc, 40, 0, 1, MOVE_STATUS, MTYPE_GRASS, &m_flags[178], &no_procs, &null_mcb},
	{_"Reversal", 100, 0, (pchar*)Reversal_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[179], &no_procs, &null_mcb},
	{_"Spite", 100, 0, (pchar*)Spite_desc, 10, 0, 1, MOVE_STATUS, MTYPE_GHOST, &m_flags[180], &no_procs, &null_mcb},
	{_"Powder Snow", 100, 40, (pchar*)Powder_Snow_desc, 25, 0, 1, MOVE_SPECIAL, MTYPE_ICE, &m_flags[181], &no_procs, &null_mcb},
	{_"Protect", 255, 0, (pchar*)Protect_desc, 10, 4, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[182], &no_procs, &null_mcb},
	{_"Mach Punch", 100, 40, (pchar*)Mach_Punch_desc, 30, 1, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[183], &no_procs, &null_mcb},
	{_"Scary Face", 100, 0, (pchar*)Scary_Face_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[184], &no_procs, &null_mcb},
	{_"Feint Attack", 255, 60, (pchar*)Feint_Attack_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[185], &no_procs, &null_mcb},
	{_"Sweet Kiss", 75, 0, (pchar*)Sweet_Kiss_desc, 10, 0, 1, MOVE_STATUS, MTYPE_FAIRY, &m_flags[186], &no_procs, &null_mcb},
	{_"Belly Drum", 255, 0, (pchar*)Belly_Drum_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[187], &no_procs, &null_mcb},
	{_"Sludge Bomb", 100, 90, (pchar*)Sludge_Bomb_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_POISON, &m_flags[188], &no_procs, &null_mcb},
	{_"Mud-Slap", 100, 20, (pchar*)Mud_Slap_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_GROUND, &m_flags[189], &no_procs, &null_mcb},
	{_"Octazooka", 85, 65, (pchar*)Octazooka_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_WATER, &m_flags[190], &no_procs, &null_mcb},
	{_"Spikes", 255, 0, (pchar*)Spikes_desc, 20, 0, 1, MOVE_STATUS, MTYPE_GROUND, &m_flags[191], &no_procs, &null_mcb},
	{_"Zap Cannon", 50, 120, (pchar*)Zap_Cannon_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_ELECTRIC, &m_flags[192], &no_procs, &null_mcb},
	{_"Foresight", 255, 0, (pchar*)Foresight_desc, 40, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[193], &no_procs, &null_mcb},
	{_"Destiny Bond", 255, 0, (pchar*)Destiny_Bond_desc, 5, 0, 1, MOVE_STATUS, MTYPE_GHOST, &m_flags[194], &no_procs, &null_mcb},
	{_"Perish Song", 255, 0, (pchar*)Perish_Song_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[195], &no_procs, &null_mcb},
	{_"Icy Wind", 95, 55, (pchar*)Icy_Wind_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_ICE, &m_flags[196], &no_procs, &null_mcb},
	{_"Detect", 255, 0, (pchar*)Detect_desc, 5, 4, 1, MOVE_STATUS, MTYPE_FIGHTING, &m_flags[197], &no_procs, &null_mcb},
	{_"Bone Rush", 90, 25, (pchar*)Bone_Rush_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[198], &no_procs, &null_mcb},
	{_"Lock-On", 255, 0, (pchar*)Lock_On_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[199], &no_procs, &null_mcb},
	{_"Outrage", 100, 120, (pchar*)Outrage_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[200], &no_procs, &null_mcb},
	{_"Sandstorm", 255, 0, (pchar*)Sandstorm_desc, 10, 0, 1, MOVE_STATUS, MTYPE_ROCK, &m_flags[201], &no_procs, &null_mcb},
	{_"Giga Drain", 100, 75, (pchar*)Giga_Drain_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_GRASS, &m_flags[202], &no_procs, &null_mcb},
	{_"Endure", 255, 0, (pchar*)Endure_desc, 10, 4, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[203], &no_procs, &null_mcb},
	{_"Charm", 100, 0, (pchar*)Charm_desc, 20, 0, 1, MOVE_STATUS, MTYPE_FAIRY, &m_flags[204], &no_procs, &null_mcb},
	{_"Rollout", 90, 30, (pchar*)Rollout_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[205], &no_procs, &null_mcb},
	{_"False Swipe", 100, 40, (pchar*)False_Swipe_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[206], &no_procs, &null_mcb},
	{_"Swagger", 85, 0, (pchar*)Swagger_desc, 15, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[207], &no_procs, &null_mcb},
	{_"Milk Drink", 255, 0, (pchar*)Milk_Drink_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[208], &no_procs, &null_mcb},
	{_"Spark", 100, 65, (pchar*)Spark_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[209], &no_procs, &null_mcb},
	{_"Fury Cutter", 95, 40, (pchar*)Fury_Cutter_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[210], &no_procs, &null_mcb},
	{_"Steel Wing", 90, 70, (pchar*)Steel_Wing_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[211], &no_procs, &null_mcb},
	{_"Mean Look", 255, 0, (pchar*)Mean_Look_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[212], &no_procs, &null_mcb},
	{_"Attract", 100, 0, (pchar*)Attract_desc, 15, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[213], &no_procs, &null_mcb},
	{_"Sleep Talk", 255, 0, (pchar*)Sleep_Talk_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[214], &no_procs, &null_mcb},
	{_"Heal Bell", 255, 0, (pchar*)Heal_Bell_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[215], &no_procs, &null_mcb},
	{_"Return", 100, 0, (pchar*)Return_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[216], &no_procs, &null_mcb},
	{_"Present", 90, 0, (pchar*)Present_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[217], &no_procs, &null_mcb},
	{_"Frustration", 100, 0, (pchar*)Frustration_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[218], &no_procs, &null_mcb},
	{_"Safeguard", 255, 0, (pchar*)Safeguard_desc, 25, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[219], &no_procs, &null_mcb},
	{_"Pain Split", 255, 0, (pchar*)Pain_Split_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[220], &no_procs, &null_mcb},
	{_"Sacred Fire", 95, 100, (pchar*)Sacred_Fire_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[221], &no_procs, &null_mcb},
	{_"Magnitude", 100, 0, (pchar*)Magnitude_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[222], &no_procs, &null_mcb},
	{_"Dynamic Punch", 50, 100, (pchar*)Dynamic_Punch_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[223], &no_procs, &null_mcb},
	{_"Megahorn", 85, 120, (pchar*)Megahorn_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[224], &no_procs, &null_mcb},
	{_"Dragon Breath", 100, 60, (pchar*)Dragon_Breath_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_DRAGON, &m_flags[225], &no_procs, &null_mcb},
	{_"Baton Pass", 255, 0, (pchar*)Baton_Pass_desc, 40, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[226], &no_procs, &null_mcb},
	{_"Encore", 100, 0, (pchar*)Encore_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[227], &no_procs, &null_mcb},
	{_"Pursuit", 100, 40, (pchar*)Pursuit_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[228], &no_procs, &null_mcb},
	{_"Rapid Spin", 100, 20, (pchar*)Rapid_Spin_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[229], &no_procs, &null_mcb},
	{_"Sweet Scent", 100, 0, (pchar*)Sweet_Scent_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[230], &no_procs, &null_mcb},
	{_"Iron Tail", 75, 100, (pchar*)Iron_Tail_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[231], &no_procs, &null_mcb},
	{_"Metal Claw", 95, 50, (pchar*)Metal_Claw_desc, 35, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[232], &no_procs, &null_mcb},
	{_"Vital Throw", 255, 70, (pchar*)Vital_Throw_desc, 10, -1, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[233], &no_procs, &null_mcb},
	{_"Morning Sun", 255, 0, (pchar*)Morning_Sun_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[234], &no_procs, &null_mcb},
	{_"Synthesis", 255, 0, (pchar*)Synthesis_desc, 5, 0, 1, MOVE_STATUS, MTYPE_GRASS, &m_flags[235], &no_procs, &null_mcb},
	{_"Moonlight", 255, 0, (pchar*)Moonlight_desc, 5, 0, 1, MOVE_STATUS, MTYPE_FAIRY, &m_flags[236], &no_procs, &null_mcb},
	{_"Hidden Power", 100, 60, (pchar*)Hidden_Power_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[237], &no_procs, &null_mcb},
	{_"Cross Chop", 80, 100, (pchar*)Cross_Chop_desc, 5, 0, 2, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[238], &no_procs, &null_mcb},
	{_"Twister", 100, 40, (pchar*)Twister_desc, 20, 0, 1, MOVE_SPECIAL, MTYPE_DRAGON, &m_flags[239], &no_procs, &null_mcb},
	{_"Rain Dance", 255, 0, (pchar*)Rain_Dance_desc, 5, 0, 1, MOVE_STATUS, MTYPE_WATER, &m_flags[240], &no_procs, &null_mcb},
	{_"Sunny Day", 255, 0, (pchar*)Sunny_Day_desc, 5, 0, 1, MOVE_STATUS, MTYPE_FIRE, &m_flags[241], &no_procs, &null_mcb},
	{_"Crunch", 100, 80, (pchar*)Crunch_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[242], &no_procs, &null_mcb},
	{_"Mirror Coat", 100, 0, (pchar*)Mirror_Coat_desc, 20, -5, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[243], &no_procs, &null_mcb},
	{_"Psych Up", 255, 0, (pchar*)Psych_Up_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[244], &no_procs, &null_mcb},
	{_"Extreme Speed", 100, 80, (pchar*)Extreme_Speed_desc, 5, 2, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[245], &no_procs, &null_mcb},
	{_"Ancient Power", 100, 60, (pchar*)Ancient_Power_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_ROCK, &m_flags[246], &no_procs, &null_mcb},
	{_"Shadow Ball", 100, 80, (pchar*)Shadow_Ball_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_GHOST, &m_flags[247], &no_procs, &null_mcb},
	{_"Future Sight", 100, 120, (pchar*)Future_Sight_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_PSYCHIC, &m_flags[248], &no_procs, &null_mcb},
	{_"Rock Smash", 100, 40, (pchar*)Rock_Smash_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[249], &no_procs, &null_mcb},
	{_"Whirlpool", 85, 35, (pchar*)Whirlpool_desc, 15, 0, 1, MOVE_SPECIAL, MTYPE_WATER, &m_flags[250], &no_procs, &null_mcb},
	{_"Beat Up", 100, 0, (pchar*)Beat_Up_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[251], &no_procs, &null_mcb},
	{_"Fake Out", 100, 40, (pchar*)Fake_Out_desc, 10, 3, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[252], &no_procs, &null_mcb},
	{_"Uproar", 100, 90, (pchar*)Uproar_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_NORMAL, &m_flags[253], &no_procs, &null_mcb},
	{_"Stockpile", 255, 0, (pchar*)Stockpile_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[254], &no_procs, &null_mcb},
	{_"Spit Up", 100, 0, (pchar*)Spit_Up_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[255], &no_procs, &null_mcb},
	{_"Swallow", 255, 0, (pchar*)Swallow_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[256], &no_procs, &null_mcb},
	{_"Heat Wave", 90, 95, (pchar*)Heat_Wave_desc, 10, 0, 1, MOVE_SPECIAL, MTYPE_FIRE, &m_flags[257], &no_procs, &null_mcb},
	{_"Hail", 255, 0, (pchar*)Hail_desc, 10, 0, 1, MOVE_STATUS, MTYPE_ICE, &m_flags[258], &no_procs, &null_mcb},
	{_"Torment", 100, 0, (pchar*)Torment_desc, 15, 0, 1, MOVE_STATUS, MTYPE_DARK, &m_flags[259], &no_procs, &null_mcb},
	{_"Flatter", 100, 0, (pchar*)Flatter_desc, 15, 0, 1, MOVE_STATUS, MTYPE_DARK, &m_flags[260], &no_procs, &null_mcb},
	{_"Will-O-Wisp", 85, 0, (pchar*)Will_O_Wisp_desc, 15, 0, 1, MOVE_STATUS, MTYPE_FIRE, &m_flags[261], &no_procs, &null_mcb},
	{_"Memento", 100, 0, (pchar*)Memento_desc, 10, 0, 1, MOVE_STATUS, MTYPE_DARK, &m_flags[262], &no_procs, &null_mcb},
	{_"Facade", 100, 70, (pchar*)Facade_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[263], &no_procs, &null_mcb},
	{_"Focus Punch", 100, 150, (pchar*)Focus_Punch_desc, 20, -3, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[264], &no_procs, &null_mcb},
	{_"Smelling Salts", 100, 70, (pchar*)Smelling_Salts_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[265], &no_procs, &null_mcb},
	{_"Follow Me", 255, 0, (pchar*)Follow_Me_desc, 20, 2, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[266], &no_procs, &null_mcb},
	{_"Nature Power", 255, 0, (pchar*)Nature_Power_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[267], &no_procs, &null_mcb},
	{_"Charge", 255, 0, (pchar*)Charge_desc, 20, 0, 1, MOVE_STATUS, MTYPE_ELECTRIC, &m_flags[268], &no_procs, &null_mcb},
	{_"Taunt", 100, 0, (pchar*)Taunt_desc, 20, 0, 1, MOVE_STATUS, MTYPE_DARK, &m_flags[269], &no_procs, &null_mcb},
	{_"Helping Hand", 255, 0, (pchar*)Helping_Hand_desc, 20, 5, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[270], &no_procs, &null_mcb},
	{_"Trick", 100, 0, (pchar*)Trick_desc, 10, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[271], &no_procs, &null_mcb},
	{_"Role Play", 255, 0, (pchar*)Role_Play_desc, 10, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[272], &no_procs, &null_mcb},
	{_"Wish", 255, 0, (pchar*)Wish_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[273], &no_procs, &null_mcb},
	{_"Assist", 255, 0, (pchar*)Assist_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[274], &no_procs, &null_mcb},
	{_"Ingrain", 255, 0, (pchar*)Ingrain_desc, 20, 0, 1, MOVE_STATUS, MTYPE_GRASS, &m_flags[275], &no_procs, &null_mcb},
	{_"Superpower", 100, 120, (pchar*)Superpower_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[276], &no_procs, &null_mcb},
	{_"Magic Coat", 255, 0, (pchar*)Magic_Coat_desc, 15, 4, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[277], &no_procs, &null_mcb},
	{_"Recycle", 255, 0, (pchar*)Recycle_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[278], &no_procs, &null_mcb},
	{_"Revenge", 100, 60, (pchar*)Revenge_desc, 10, -4, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[279], &no_procs, &null_mcb},
	{_"Brick Break", 100, 75, (pchar*)Brick_Break_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[280], &no_procs, &null_mcb},
	{_"Yawn", 255, 0, (pchar*)Yawn_desc, 10, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[281], &no_procs, &null_mcb},
	{_"Knock Off", 100, 65, (pchar*)Knock_Off_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[282], &no_procs, &null_mcb},
	{_"Endeavor", 100, 0, (pchar*)Endeavor_desc, 5, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[283], &no_procs, &null_mcb},
	{_"Eruption", 100, 150, (pchar*)Eruption_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_FIRE, &m_flags[284], &no_procs, &null_mcb},
	{_"Skill Swap", 255, 0, (pchar*)Skill_Swap_desc, 10, 0, 1,MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[285], &no_procs, &null_mcb},
	{_"Imprison", 255, 0, (pchar*)Imprison_desc, 10, 0, 1, MOVE_STATUS, MTYPE_PSYCHIC, &m_flags[286], &no_procs, &null_mcb},
	{_"Refresh", 255, 0, (pchar*)Refresh_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[287], &no_procs, &null_mcb},
	{_"Grudge", 255, 0, (pchar*)Grudge_desc, 5, 0, 1, MOVE_STATUS, MTYPE_GHOST, &m_flags[288], &no_procs, &null_mcb},
	{_"Snatch", 255, 0, (pchar*)Snatch_desc, 10, 4, 1, MOVE_STATUS, MTYPE_DARK, &m_flags[289], &no_procs, &null_mcb},
	{_"Secret Power", 100, 70, (pchar*)Secret_Power_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[290], &no_procs, &null_mcb},
	{_"Dive", 100, 80, (pchar*)Dive_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[291], &no_procs, &null_mcb},
	{_"Arm Thrust", 100, 15, (pchar*)Arm_Thrust_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[292], &no_procs, &null_mcb},
	{_"Camouflage", 255, 0, (pchar*)Camouflage_desc, 20, 0, 1, MOVE_STATUS, MTYPE_NORMAL, &m_flags[293], &no_procs, &null_mcb},
	{_"Tail Glow", 255, 0, (pchar*)Tail_Glow_desc, 20, 0, 1, MOVE_STATUS, MTYPE_BUG, &m_flags[294], &no_procs, &null_mcb},
	{_"Luster Purge", 100, 70, (pchar*)Luster_Purge_desc, 5, 0, 1, MOVE_SPECIAL, MTYPE_PSYCHIC, &m_flags[295], &no_procs, &null_mcb},
	{_"Mist Ball", 100, 70, (pchar*)Mist_Ball_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[296], &no_procs, &null_mcb},
	{_"Feather Dance", 100, 0, (pchar*)Feather_Dance_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[297], &no_procs, &null_mcb},
	{_"Teeter Dance", 100, 0, (pchar*)Teeter_Dance_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[298], &no_procs, &null_mcb},
	{_"Blaze Kick", 90, 85, (pchar*)Blaze_Kick_desc, 10, 0, 2, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[299], &no_procs, &null_mcb},
	{_"Mud Sport", 255, 0, (pchar*)Mud_Sport_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[300], &no_procs, &null_mcb},
	{_"Ice Ball", 90, 30, (pchar*)Ice_Ball_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[301], &no_procs, &null_mcb},
	{_"Needle Arm", 100, 60, (pchar*)Needle_Arm_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[302], &no_procs, &null_mcb},
	{_"Slack Off", 255, 0, (pchar*)Slack_Off_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[303], &no_procs, &null_mcb},
	{_"Hyper Voice", 100, 90, (pchar*)Hyper_Voice_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[304], &no_procs, &null_mcb},
	{_"Poison Fang", 100, 50, (pchar*)Poison_Fang_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[305], &no_procs, &null_mcb},
	{_"Crush Claw", 95, 75, (pchar*)Crush_Claw_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[306], &no_procs, &null_mcb},
	{_"Blast Burn", 90, 150, (pchar*)Blast_Burn_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[307], &no_procs, &null_mcb},
	{_"Hydro Cannon", 90, 150, (pchar*)Hydro_Cannon_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[308], &no_procs, &null_mcb},
	{_"Meteor Mash", 90, 90, (pchar*)Meteor_Mash_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[309], &no_procs, &null_mcb},
	{_"Astonish", 100, 30, (pchar*)Astonish_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[310], &no_procs, &null_mcb},
	{_"Weather Ball", 100, 50, (pchar*)Weather_Ball_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[311], &no_procs, &null_mcb},
	{_"Aromatherapy", 255, 0, (pchar*)Aromatherapy_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[312], &no_procs, &null_mcb},
	{_"Fake Tears", 100, 0, (pchar*)Fake_Tears_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[313], &no_procs, &null_mcb},
	{_"Air Cutter", 95, 60, (pchar*)Air_Cutter_desc, 25, 0, 2, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[314], &no_procs, &null_mcb},
	{_"Overheat", 90, 130, (pchar*)Overheat_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[315], &no_procs, &null_mcb},
	{_"Odor Sleuth", 255, 0, (pchar*)Odor_Sleuth_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[316], &no_procs, &null_mcb},
	{_"Rock Tomb", 95, 60, (pchar*)Rock_Tomb_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[317], &no_procs, &null_mcb},
	{_"Silver Wind", 100, 60, (pchar*)Silver_Wind_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[318], &no_procs, &null_mcb},
	{_"Metal Sound", 85, 0, (pchar*)Metal_Sound_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[319], &no_procs, &null_mcb},
	{_"Grass Whistle", 55, 0, (pchar*)Grass_Whistle_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[320], &no_procs, &null_mcb},
	{_"Tickle", 100, 0, (pchar*)Tickle_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[321], &no_procs, &null_mcb},
	{_"Cosmic Power", 255, 0, (pchar*)Cosmic_Power_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[322], &no_procs, &null_mcb},
	{_"Water Spout", 100, 150, (pchar*)Water_Spout_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[323], &no_procs, &null_mcb},
	{_"Signal Beam", 100, 75, (pchar*)Signal_Beam_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[324], &no_procs, &null_mcb},
	{_"Shadow Punch", 255, 60, (pchar*)Shadow_Punch_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[325], &no_procs, &null_mcb},
	{_"Extrasensory", 100, 80, (pchar*)Extrasensory_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[326], &no_procs, &null_mcb},
	{_"Sky Uppercut", 90, 85, (pchar*)Sky_Uppercut_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[327], &no_procs, &null_mcb},
	{_"Sand Tomb", 85, 35, (pchar*)Sand_Tomb_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[328], &no_procs, &null_mcb},
	{_"Sheer Cold", 30, 0, (pchar*)Sheer_Cold_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[329], &no_procs, &null_mcb},
	{_"Muddy Water", 85, 90, (pchar*)Muddy_Water_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[330], &no_procs, &null_mcb},
	{_"Bullet Seed", 100, 25, (pchar*)Bullet_Seed_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[331], &no_procs, &null_mcb},
	{_"Aerial Ace", 255, 60, (pchar*)Aerial_Ace_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[332], &no_procs, &null_mcb},
	{_"Icicle Spear", 100, 25, (pchar*)Icicle_Spear_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[333], &no_procs, &null_mcb},
	{_"Iron Defense", 255, 0, (pchar*)Iron_Defense_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[334], &no_procs, &null_mcb},
	{_"Block", 255, 0, (pchar*)Block_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[335], &no_procs, &null_mcb},
	{_"Howl", 255, 0, (pchar*)Howl_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[336], &no_procs, &null_mcb},
	{_"Dragon Claw", 100, 80, (pchar*)Dragon_Claw_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[337], &no_procs, &null_mcb},
	{_"Frenzy Plant", 90, 150, (pchar*)Frenzy_Plant_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[338], &no_procs, &null_mcb},
	{_"Bulk Up", 255, 0, (pchar*)Bulk_Up_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[339], &no_procs, &null_mcb},
	{_"Bounce", 85, 85, (pchar*)Bounce_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[340], &no_procs, &null_mcb},
	{_"Mud Shot", 95, 55, (pchar*)Mud_Shot_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[341], &no_procs, &null_mcb},
	{_"Poison Tail", 100, 50, (pchar*)Poison_Tail_desc, 25, 0, 2, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[342], &no_procs, &null_mcb},
	{_"Covet", 100, 60, (pchar*)Covet_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[343], &no_procs, &null_mcb},
	{_"Volt Tackle", 100, 120, (pchar*)Volt_Tackle_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[344], &no_procs, &null_mcb},
	{_"Magical Leaf", 255, 60, (pchar*)Magical_Leaf_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[345], &no_procs, &null_mcb},
	{_"Water Sport", 255, 0, (pchar*)Water_Sport_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[346], &no_procs, &null_mcb},
	{_"Calm Mind", 255, 0, (pchar*)Calm_Mind_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[347], &no_procs, &null_mcb},
	{_"Leaf Blade", 100, 90, (pchar*)Leaf_Blade_desc, 15, 0, 2, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[348], &no_procs, &null_mcb},
	{_"Dragon Dance", 255, 0, (pchar*)Dragon_Dance_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[349], &no_procs, &null_mcb},
	{_"Rock Blast", 90, 25, (pchar*)Rock_Blast_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[350], &no_procs, &null_mcb},
	{_"Shock Wave", 255, 60, (pchar*)Shock_Wave_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[351], &no_procs, &null_mcb},
	{_"Water Pulse", 100, 60, (pchar*)Water_Pulse_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[352], &no_procs, &null_mcb},
	{_"Doom Desire", 100, 140, (pchar*)Doom_Desire_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[353], &no_procs, &null_mcb},
	{_"Psycho Boost", 90, 140, (pchar*)Psycho_Boost_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[354], &no_procs, &null_mcb},
	{_"Roost", 255, 0, (pchar*)Roost_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[355], &no_procs, &null_mcb},
	{_"Gravity", 255, 0, (pchar*)Gravity_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[356], &no_procs, &null_mcb},
	{_"Miracle Eye", 255, 0, (pchar*)Miracle_Eye_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[357], &no_procs, &null_mcb},
	{_"Wake-Up Slap", 100, 70, (pchar*)Wake_Up_Slap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[358], &no_procs, &null_mcb},
	{_"Hammer Arm", 90, 100, (pchar*)Hammer_Arm_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[359], &no_procs, &null_mcb},
	{_"Gyro Ball", 100, 0, (pchar*)Gyro_Ball_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[360], &no_procs, &null_mcb},
	{_"Healing Wish", 255, 0, (pchar*)Healing_Wish_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[361], &no_procs, &null_mcb},
	{_"Brine", 100, 65, (pchar*)Brine_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[362], &no_procs, &null_mcb},
	{_"Natural Gift", 100, 0, (pchar*)Natural_Gift_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[363], &no_procs, &null_mcb},
	{_"Feint", 100, 30, (pchar*)Feint_desc, 10, 2, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[364], &no_procs, &null_mcb},
	{_"Pluck", 100, 60, (pchar*)Pluck_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[365], &no_procs, &null_mcb},
	{_"Tailwind", 255, 0, (pchar*)Tailwind_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[366], &no_procs, &null_mcb},
	{_"Acupressure", 255, 0, (pchar*)Acupressure_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[367], &no_procs, &null_mcb},
	{_"Metal Burst", 100, 0, (pchar*)Metal_Burst_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[368], &no_procs, &null_mcb},
	{_"U-turn", 100, 70, (pchar*)U_turn_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[369], &no_procs, &null_mcb},
	{_"Close Combat", 100, 120, (pchar*)Close_Combat_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[370], &no_procs, &null_mcb},
	{_"Payback", 100, 50, (pchar*)Payback_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[371], &no_procs, &null_mcb},
	{_"Assurance", 100, 60, (pchar*)Assurance_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[372], &no_procs, &null_mcb},
	{_"Embargo", 100, 0, (pchar*)Embargo_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[373], &no_procs, &null_mcb},
	{_"Fling", 100, 0, (pchar*)Fling_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[374], &no_procs, &null_mcb},
	{_"Psycho Shift", 100, 0, (pchar*)Psycho_Shift_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[375], &no_procs, &null_mcb},
	{_"Trump Card", 255, 0, (pchar*)Trump_Card_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[376], &no_procs, &null_mcb},
	{_"Heal Block", 100, 0, (pchar*)Heal_Block_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[377], &no_procs, &null_mcb},
	{_"Wring Out", 100, 0, (pchar*)Wring_Out_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[378], &no_procs, &null_mcb},
	{_"Power Trick", 255, 0, (pchar*)Power_Trick_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[379], &no_procs, &null_mcb},
	{_"Gastro Acid", 100, 0, (pchar*)Gastro_Acid_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[380], &no_procs, &null_mcb},
	{_"Lucky Chant", 255, 0, (pchar*)Lucky_Chant_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[381], &no_procs, &null_mcb},
	{_"Me First", 255, 0, (pchar*)Me_First_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[382], &no_procs, &null_mcb},
	{_"Copycat", 255, 0, (pchar*)Copycat_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[383], &no_procs, &null_mcb},
	{_"Power Swap", 255, 0, (pchar*)Power_Swap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[384], &no_procs, &null_mcb},
	{_"Guard Swap", 255, 0, (pchar*)Guard_Swap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[385], &no_procs, &null_mcb},
	{_"Punishment", 100, 0, (pchar*)Punishment_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[386], &no_procs, &null_mcb},
	{_"Last Resort", 100, 140, (pchar*)Last_Resort_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[387], &no_procs, &null_mcb},
	{_"Worry Seed", 100, 0, (pchar*)Worry_Seed_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[388], &no_procs, &null_mcb},
	{_"Sucker Punch", 100, 70, (pchar*)Sucker_Punch_desc, 5, 1, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[389], &no_procs, &null_mcb},
	{_"Toxic Spikes", 255, 0, (pchar*)Toxic_Spikes_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[390], &no_procs, &null_mcb},
	{_"Heart Swap", 255, 0, (pchar*)Heart_Swap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[391], &no_procs, &null_mcb},
	{_"Aqua Ring", 255, 0, (pchar*)Aqua_Ring_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[392], &no_procs, &null_mcb},
	{_"Magnet Rise", 255, 0, (pchar*)Magnet_Rise_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[393], &no_procs, &null_mcb},
	{_"Flare Blitz", 100, 120, (pchar*)Flare_Blitz_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[394], &no_procs, &null_mcb},
	{_"Force Palm", 100, 60, (pchar*)Force_Palm_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[395], &no_procs, &null_mcb},
	{_"Aura Sphere", 255, 80, (pchar*)Aura_Sphere_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[396], &no_procs, &null_mcb},
	{_"Rock Polish", 255, 0, (pchar*)Rock_Polish_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[397], &no_procs, &null_mcb},
	{_"Poison Jab", 100, 80, (pchar*)Poison_Jab_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[398], &no_procs, &null_mcb},
	{_"Dark Pulse", 100, 80, (pchar*)Dark_Pulse_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[399], &no_procs, &null_mcb},
	{_"Night Slash", 100, 70, (pchar*)Night_Slash_desc, 15, 0, 2, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[400], &no_procs, &null_mcb},
	{_"Aqua Tail", 90, 90, (pchar*)Aqua_Tail_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[401], &no_procs, &null_mcb},
	{_"Seed Bomb", 100, 80, (pchar*)Seed_Bomb_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[402], &no_procs, &null_mcb},
	{_"Air Slash", 95, 75, (pchar*)Air_Slash_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[403], &no_procs, &null_mcb},
	{_"X-Scissor", 100, 80, (pchar*)X_Scissor_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[404], &no_procs, &null_mcb},
	{_"Bug Buzz", 100, 90, (pchar*)Bug_Buzz_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[405], &no_procs, &null_mcb},
	{_"Dragon Pulse", 100, 85, (pchar*)Dragon_Pulse_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[406], &no_procs, &null_mcb},
	{_"Dragon Rush", 75, 100, (pchar*)Dragon_Rush_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[407], &no_procs, &null_mcb},
	{_"Power Gem", 100, 80, (pchar*)Power_Gem_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[408], &no_procs, &null_mcb},
	{_"Drain Punch", 100, 75, (pchar*)Drain_Punch_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[409], &no_procs, &null_mcb},
	{_"Vacuum Wave", 100, 40, (pchar*)Vacuum_Wave_desc, 30, 1, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[410], &no_procs, &null_mcb},
	{_"Focus Blast", 70, 120, (pchar*)Focus_Blast_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[411], &no_procs, &null_mcb},
	{_"Energy Ball", 100, 90, (pchar*)Energy_Ball_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[412], &no_procs, &null_mcb},
	{_"Brave Bird", 100, 120, (pchar*)Brave_Bird_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[413], &no_procs, &null_mcb},
	{_"Earth Power", 100, 90, (pchar*)Earth_Power_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[414], &no_procs, &null_mcb},
	{_"Switcheroo", 100, 0, (pchar*)Switcheroo_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[415], &no_procs, &null_mcb},
	{_"Giga Impact", 90, 150, (pchar*)Giga_Impact_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[416], &no_procs, &null_mcb},
	{_"Nasty Plot", 255, 0, (pchar*)Nasty_Plot_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[417], &no_procs, &null_mcb},
	{_"Bullet Punch", 100, 40, (pchar*)Bullet_Punch_desc, 30, 1, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[418], &no_procs, &null_mcb},
	{_"Avalanche", 100, 60, (pchar*)Avalanche_desc, 10, -4, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[419], &no_procs, &null_mcb},
	{_"Ice Shard", 100, 40, (pchar*)Ice_Shard_desc, 30, 1, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[420], &no_procs, &null_mcb},
	{_"Shadow Claw", 100, 70, (pchar*)Shadow_Claw_desc, 15, 0, 2, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[421], &no_procs, &null_mcb},
	{_"Thunder Fang", 95, 65, (pchar*)Thunder_Fang_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[422], &no_procs, &null_mcb},
	{_"Ice Fang", 95, 65, (pchar*)Ice_Fang_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[423], &no_procs, &null_mcb},
	{_"Fire Fang", 95, 65, (pchar*)Fire_Fang_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[424], &no_procs, &null_mcb},
	{_"Shadow Sneak", 100, 40, (pchar*)Shadow_Sneak_desc, 30, 1, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[425], &no_procs, &null_mcb},
	{_"Mud Bomb", 85, 65, (pchar*)Mud_Bomb_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[426], &no_procs, &null_mcb},
	{_"Psycho Cut", 100, 70, (pchar*)Psycho_Cut_desc, 20, 0, 2, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[427], &no_procs, &null_mcb},
	{_"Zen Headbutt", 90, 80, (pchar*)Zen_Headbutt_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[428], &no_procs, &null_mcb},
	{_"Mirror Shot", 85, 65, (pchar*)Mirror_Shot_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[429], &no_procs, &null_mcb},
	{_"Flash Cannon", 100, 80, (pchar*)Flash_Cannon_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[430], &no_procs, &null_mcb},
	{_"Rock Climb", 85, 90, (pchar*)Rock_Climb_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[431], &no_procs, &null_mcb},
	{_"Defog", 255, 0, (pchar*)Defog_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[432], &no_procs, &null_mcb},
	{_"Trick Room", 255, 0, (pchar*)Trick_Room_desc, 5, -7, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[433], &no_procs, &null_mcb},
	{_"Draco Meteor", 90, 130, (pchar*)Draco_Meteor_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[434], &no_procs, &null_mcb},
	{_"Discharge", 100, 80, (pchar*)Discharge_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[435], &no_procs, &null_mcb},
	{_"Lava Plume", 100, 80, (pchar*)Lava_Plume_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[436], &no_procs, &null_mcb},
	{_"Leaf Storm", 90, 130, (pchar*)Leaf_Storm_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[437], &no_procs, &null_mcb},
	{_"Power Whip", 85, 120, (pchar*)Power_Whip_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[438], &no_procs, &null_mcb},
	{_"Rock Wrecker", 90, 150, (pchar*)Rock_Wrecker_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[439], &no_procs, &null_mcb},
	{_"Cross Poison", 100, 70, (pchar*)Cross_Poison_desc, 20, 0, 2, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[440], &no_procs, &null_mcb},
	{_"Gunk Shot", 80, 120, (pchar*)Gunk_Shot_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[441], &no_procs, &null_mcb},
	{_"Iron Head", 100, 80, (pchar*)Iron_Head_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[442], &no_procs, &null_mcb},
	{_"Magnet Bomb", 255, 60, (pchar*)Magnet_Bomb_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[443], &no_procs, &null_mcb},
	{_"Stone Edge", 80, 100, (pchar*)Stone_Edge_desc, 5, 0, 2, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[444], &no_procs, &null_mcb},
	{_"Captivate", 100, 0, (pchar*)Captivate_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[445], &no_procs, &null_mcb},
	{_"Stealth Rock", 255, 0, (pchar*)Stealth_Rock_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[446], &no_procs, &null_mcb},
	{_"Grass Knot", 100, 0, (pchar*)Grass_Knot_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[447], &no_procs, &null_mcb},
	{_"Chatter", 100, 65, (pchar*)Chatter_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[448], &no_procs, &null_mcb},
	{_"Judgment", 100, 100, (pchar*)Judgment_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[449], &no_procs, &null_mcb},
	{_"Bug Bite", 100, 60, (pchar*)Bug_Bite_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[450], &no_procs, &null_mcb},
	{_"Charge Beam", 90, 50, (pchar*)Charge_Beam_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[451], &no_procs, &null_mcb},
	{_"Wood Hammer", 100, 120, (pchar*)Wood_Hammer_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[452], &no_procs, &null_mcb},
	{_"Aqua Jet", 100, 40, (pchar*)Aqua_Jet_desc, 20, 1, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[453], &no_procs, &null_mcb},
	{_"Attack Order", 100, 90, (pchar*)Attack_Order_desc, 15, 0, 2, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[454], &no_procs, &null_mcb},
	{_"Defend Order", 255, 0, (pchar*)Defend_Order_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[455], &no_procs, &null_mcb},
	{_"Heal Order", 255, 0, (pchar*)Heal_Order_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[456], &no_procs, &null_mcb},
	{_"Head Smash", 80, 150, (pchar*)Head_Smash_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[457], &no_procs, &null_mcb},
	{_"Double Hit", 90, 35, (pchar*)Double_Hit_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[458], &no_procs, &null_mcb},
	{_"Roar of Time", 90, 150, (pchar*)Roar_of_Time_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[459], &no_procs, &null_mcb},
	{_"Spacial Rend", 95, 100, (pchar*)Spacial_Rend_desc, 5, 0, 2, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[460], &no_procs, &null_mcb},
	{_"Lunar Dance", 255, 0, (pchar*)Lunar_Dance_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[461], &no_procs, &null_mcb},
	{_"Crush Grip", 100, 0, (pchar*)Crush_Grip_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[462], &no_procs, &null_mcb},
	{_"Magma Storm", 75, 100, (pchar*)Magma_Storm_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[463], &no_procs, &null_mcb},
	{_"Dark Void", 50, 0, (pchar*)Dark_Void_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[464], &no_procs, &null_mcb},
	{_"Seed Flare", 85, 120, (pchar*)Seed_Flare_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[465], &no_procs, &null_mcb},
	{_"Ominous Wind", 100, 60, (pchar*)Ominous_Wind_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[466], &no_procs, &null_mcb},
	{_"Shadow Force", 100, 120, (pchar*)Shadow_Force_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[467], &no_procs, &null_mcb},
	{_"Hone Claws", 255, 0, (pchar*)Hone_Claws_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[468], &no_procs, &null_mcb},
	{_"Wide Guard", 255, 0, (pchar*)Wide_Guard_desc, 10, 3, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[469], &no_procs, &null_mcb},
	{_"Guard Split", 255, 0, (pchar*)Guard_Split_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[470], &no_procs, &null_mcb},
	{_"Power Split", 255, 0, (pchar*)Power_Split_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[471], &no_procs, &null_mcb},
	{_"Wonder Room", 255, 0, (pchar*)Wonder_Room_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[472], &no_procs, &null_mcb},
	{_"Psyshock", 100, 80, (pchar*)Psyshock_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[473], &no_procs, &null_mcb},
	{_"Venoshock", 100, 65, (pchar*)Venoshock_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[474], &no_procs, &null_mcb},
	{_"Autotomize", 255, 0, (pchar*)Autotomize_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[475], &no_procs, &null_mcb},
	{_"Rage Powder", 255, 0, (pchar*)Rage_Powder_desc, 20, 2, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[476], &no_procs, &null_mcb},
	{_"Telekinesis", 255, 0, (pchar*)Telekinesis_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[477], &no_procs, &null_mcb},
	{_"Magic Room", 255, 0, (pchar*)Magic_Room_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[478], &no_procs, &null_mcb},
	{_"Smack Down", 100, 50, (pchar*)Smack_Down_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[479], &no_procs, &null_mcb},
	{_"Storm Throw", 100, 60, (pchar*)Storm_Throw_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[480], &no_procs, &null_mcb},
	{_"Flame Burst", 100, 70, (pchar*)Flame_Burst_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[481], &no_procs, &null_mcb},
	{_"Sludge Wave", 100, 95, (pchar*)Sludge_Wave_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[482], &no_procs, &null_mcb},
	{_"Quiver Dance", 255, 0, (pchar*)Quiver_Dance_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[483], &no_procs, &null_mcb},
	{_"Heavy Slam", 100, 0, (pchar*)Heavy_Slam_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[484], &no_procs, &null_mcb},
	{_"Synchronoise", 100, 120, (pchar*)Synchronoise_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[485], &no_procs, &null_mcb},
	{_"Electro Ball", 100, 0, (pchar*)Electro_Ball_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[486], &no_procs, &null_mcb},
	{_"Soak", 100, 0, (pchar*)Soak_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[487], &no_procs, &null_mcb},
	{_"Flame Charge", 100, 50, (pchar*)Flame_Charge_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[488], &no_procs, &null_mcb},
	{_"Coil", 255, 0, (pchar*)Coil_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[489], &no_procs, &null_mcb},
	{_"Low Sweep", 100, 65, (pchar*)Low_Sweep_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[490], &no_procs, &null_mcb},
	{_"Acid Spray", 100, 40, (pchar*)Acid_Spray_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[491], &no_procs, &null_mcb},
	{_"Foul Play", 100, 95, (pchar*)Foul_Play_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[492], &no_procs, &null_mcb},
	{_"Simple Beam", 100, 0, (pchar*)Simple_Beam_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[493], &no_procs, &null_mcb},
	{_"Entrainment", 100, 0, (pchar*)Entrainment_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[494], &no_procs, &null_mcb},
	{_"After You", 255, 0, (pchar*)After_You_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[495], &no_procs, &null_mcb},
	{_"Round", 100, 60, (pchar*)Round_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[496], &no_procs, &null_mcb},
	{_"Echoed Voice", 100, 40, (pchar*)Echoed_Voice_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[497], &no_procs, &null_mcb},
	{_"Chip Away", 100, 70, (pchar*)Chip_Away_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[498], &no_procs, &null_mcb},
	{_"Clear Smog", 255, 50, (pchar*)Clear_Smog_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[499], &no_procs, &null_mcb},
	{_"Stored Power", 100, 20, (pchar*)Stored_Power_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[500], &no_procs, &null_mcb},
	{_"Quick Guard", 255, 0, (pchar*)Quick_Guard_desc, 15, 3, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[501], &no_procs, &null_mcb},
	{_"Ally Switch", 255, 0, (pchar*)Ally_Switch_desc, 15, 2, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[502], &no_procs, &null_mcb},
	{_"Scald", 100, 80, (pchar*)Scald_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[503], &no_procs, &null_mcb},
	{_"Shell Smash", 255, 0, (pchar*)Shell_Smash_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[504], &no_procs, &null_mcb},
	{_"Heal Pulse", 255, 0, (pchar*)Heal_Pulse_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[505], &no_procs, &null_mcb},
	{_"Hex", 100, 65, (pchar*)Hex_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[506], &no_procs, &null_mcb},
	{_"Sky Drop", 100, 60, (pchar*)Sky_Drop_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[507], &no_procs, &null_mcb},
	{_"Shift Gear", 255, 0, (pchar*)Shift_Gear_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[508], &no_procs, &null_mcb},
	{_"Circle Throw", 90, 60, (pchar*)Circle_Throw_desc, 10, -6, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[509], &no_procs, &null_mcb},
	{_"Incinerate", 100, 60, (pchar*)Incinerate_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[510], &no_procs, &null_mcb},
	{_"Quash", 100, 0, (pchar*)Quash_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[511], &no_procs, &null_mcb},
	{_"Acrobatics", 100, 55, (pchar*)Acrobatics_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[512], &no_procs, &null_mcb},
	{_"Reflect Type", 255, 0, (pchar*)Reflect_Type_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[513], &no_procs, &null_mcb},
	{_"Retaliate", 100, 70, (pchar*)Retaliate_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[514], &no_procs, &null_mcb},
	{_"Final Gambit", 100, 0, (pchar*)Final_Gambit_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[515], &no_procs, &null_mcb},
	{_"Bestow", 255, 0, (pchar*)Bestow_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[516], &no_procs, &null_mcb},
	{_"Inferno", 50, 100, (pchar*)Inferno_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[517], &no_procs, &null_mcb},
	{_"Water Pledge", 100, 80, (pchar*)Water_Pledge_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[518], &no_procs, &null_mcb},
	{_"Fire Pledge", 100, 80, (pchar*)Fire_Pledge_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[519], &no_procs, &null_mcb},
	{_"Grass Pledge", 100, 80, (pchar*)Grass_Pledge_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[520], &no_procs, &null_mcb},
	{_"Volt Switch", 100, 70, (pchar*)Volt_Switch_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[521], &no_procs, &null_mcb},
	{_"Struggle Bug", 100, 50, (pchar*)Struggle_Bug_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[522], &no_procs, &null_mcb},
	{_"Bulldoze", 100, 60, (pchar*)Bulldoze_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[523], &no_procs, &null_mcb},
	{_"Frost Breath", 90, 60, (pchar*)Frost_Breath_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[524], &no_procs, &null_mcb},
	{_"Dragon Tail", 90, 60, (pchar*)Dragon_Tail_desc, 10, -6, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[525], &no_procs, &null_mcb},
	{_"Work Up", 255, 0, (pchar*)Work_Up_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[526], &no_procs, &null_mcb},
	{_"Electroweb", 95, 55, (pchar*)Electroweb_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[527], &no_procs, &null_mcb},
	{_"Wild Charge", 100, 90, (pchar*)Wild_Charge_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[528], &no_procs, &null_mcb},
	{_"Drill Run", 95, 80, (pchar*)Drill_Run_desc, 10, 0, 2, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[529], &no_procs, &null_mcb},
	{_"Dual Chop", 90, 40, (pchar*)Dual_Chop_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[530], &no_procs, &null_mcb},
	{_"Heart Stamp", 100, 60, (pchar*)Heart_Stamp_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[531], &no_procs, &null_mcb},
	{_"Horn Leech", 100, 75, (pchar*)Horn_Leech_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[532], &no_procs, &null_mcb},
	{_"Sacred Sword", 100, 90, (pchar*)Sacred_Sword_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[533], &no_procs, &null_mcb},
	{_"Razor Shell", 95, 75, (pchar*)Razor_Shell_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[534], &no_procs, &null_mcb},
	{_"Heat Crash", 100, 0, (pchar*)Heat_Crash_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[535], &no_procs, &null_mcb},
	{_"Leaf Tornado", 90, 65, (pchar*)Leaf_Tornado_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[536], &no_procs, &null_mcb},
	{_"Steamroller", 100, 65, (pchar*)Steamroller_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[537], &no_procs, &null_mcb},
	{_"Cotton Guard", 255, 0, (pchar*)Cotton_Guard_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[538], &no_procs, &null_mcb},
	{_"Night Daze", 95, 85, (pchar*)Night_Daze_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[539], &no_procs, &null_mcb},
	{_"Psystrike", 100, 100, (pchar*)Psystrike_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[540], &no_procs, &null_mcb},
	{_"Tail Slap", 85, 25, (pchar*)Tail_Slap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[541], &no_procs, &null_mcb},
	{_"Hurricane", 70, 110, (pchar*)Hurricane_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[542], &no_procs, &null_mcb},
	{_"Head Charge", 100, 120, (pchar*)Head_Charge_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[543], &no_procs, &null_mcb},
	{_"Gear Grind", 85, 50, (pchar*)Gear_Grind_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[544], &no_procs, &null_mcb},
	{_"Searing Shot", 100, 100, (pchar*)Searing_Shot_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[545], &no_procs, &null_mcb},
	{_"Techno Blast", 100, 120, (pchar*)Techno_Blast_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[546], &no_procs, &null_mcb},
	{_"Relic Song", 100, 75, (pchar*)Relic_Song_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[547], &no_procs, &null_mcb},
	{_"Secret Sword", 100, 85, (pchar*)Secret_Sword_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[548], &no_procs, &null_mcb},
	{_"Glaciate", 95, 65, (pchar*)Glaciate_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[549], &no_procs, &null_mcb},
	{_"Bolt Strike", 85, 130, (pchar*)Bolt_Strike_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[550], &no_procs, &null_mcb},
	{_"Blue Flare", 85, 130, (pchar*)Blue_Flare_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[551], &no_procs, &null_mcb},
	{_"Fiery Dance", 100, 80, (pchar*)Fiery_Dance_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[552], &no_procs, &null_mcb},
	{_"Freeze Shock", 90, 140, (pchar*)Freeze_Shock_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[553], &no_procs, &null_mcb},
	{_"Ice Burn", 90, 140, (pchar*)Ice_Burn_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[554], &no_procs, &null_mcb},
	{_"Snarl", 95, 55, (pchar*)Snarl_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[555], &no_procs, &null_mcb},
	{_"Icicle Crash", 90, 85, (pchar*)Icicle_Crash_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[556], &no_procs, &null_mcb},
	{_"V-create", 95, 180, (pchar*)V_create_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[557], &no_procs, &null_mcb},
	{_"Fusion Flare", 100, 100, (pchar*)Fusion_Flare_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[558], &no_procs, &null_mcb},
	{_"Fusion Bolt", 100, 100, (pchar*)Fusion_Bolt_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[559], &no_procs, &null_mcb},
	{_"Flying Press", 95, 100, (pchar*)Flying_Press_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[560], &no_procs, &null_mcb},
	{_"Mat Block", 255, 0, (pchar*)Mat_Block_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[561], &no_procs, &null_mcb},
	{_"Belch", 90, 120, (pchar*)Belch_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[562], &no_procs, &null_mcb},
	{_"Rototiller", 255, 0, (pchar*)Rototiller_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[563], &no_procs, &null_mcb},
	{_"Sticky Web", 255, 0, (pchar*)Sticky_Web_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[564], &no_procs, &null_mcb},
	{_"Fell Stinger", 100, 50, (pchar*)Fell_Stinger_desc, 25, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[565], &no_procs, &null_mcb},
	{_"Phantom Force", 100, 90, (pchar*)Phantom_Force_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[566], &no_procs, &null_mcb},
	{_"Trick-or-Treat", 100, 0, (pchar*)Trick_or_Treat_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[567], &no_procs, &null_mcb},
	{_"Noble Roar", 100, 0, (pchar*)Noble_Roar_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[568], &no_procs, &null_mcb},
	{_"Ion Deluge", 255, 0, (pchar*)Ion_Deluge_desc, 25, 1, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[569], &no_procs, &null_mcb},
	{_"Parabolic Charge", 100, 65, (pchar*)Parabolic_Charge_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[570], &no_procs, &null_mcb},
	{_"Forest‘s Curse", 100, 0, (pchar*)Forests_Curse_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[571], &no_procs, &null_mcb},
	{_"Petal Blizzard", 100, 90, (pchar*)Petal_Blizzard_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[572], &no_procs, &null_mcb},
	{_"Freeze-Dry", 100, 70, (pchar*)Freeze_Dry_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[573], &no_procs, &null_mcb},
	{_"Disarming Voice", 255, 40, (pchar*)Disarming_Voice_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[574], &no_procs, &null_mcb},
	{_"Parting Shot", 100, 0, (pchar*)Parting_Shot_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[575], &no_procs, &null_mcb},
	{_"Topsy-Turvy", 255, 0, (pchar*)Topsy_Turvy_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[576], &no_procs, &null_mcb},
	{_"Draining Kiss", 100, 50, (pchar*)Draining_Kiss_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[577], &no_procs, &null_mcb},
	{_"Crafty Shield", 255, 0, (pchar*)Crafty_Shield_desc, 10, 3, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[578], &no_procs, &null_mcb},
	{_"Flower Shield", 255, 0, (pchar*)Flower_Shield_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[579], &no_procs, &null_mcb},
	{_"Grassy Terrain", 255, 0, (pchar*)Grassy_Terrain_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[580], &no_procs, &null_mcb},
	{_"Misty Terrain", 255, 0, (pchar*)Misty_Terrain_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[581], &no_procs, &null_mcb},
	{_"Electrify", 255, 0, (pchar*)Electrify_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[582], &no_procs, &null_mcb},
	{_"Play Rough", 90, 90, (pchar*)Play_Rough_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[583], &no_procs, &null_mcb},
	{_"Fairy Wind", 100, 40, (pchar*)Fairy_Wind_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[584], &no_procs, &null_mcb},
	{_"Moonblast", 100, 95, (pchar*)Moonblast_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[585], &no_procs, &null_mcb},
	{_"Boomburst", 100, 140, (pchar*)Boomburst_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[586], &no_procs, &null_mcb},
	{_"Fairy Lock", 255, 0, (pchar*)Fairy_Lock_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[587], &no_procs, &null_mcb},
	{_"King‘s Shield", 255, 0, (pchar*)Kings_Shield_desc, 10, 4, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[588], &no_procs, &null_mcb},
	{_"Play Nice", 255, 0, (pchar*)Play_Nice_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[589], &no_procs, &null_mcb},
	{_"Confide", 255, 0, (pchar*)Confide_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[590], &no_procs, &null_mcb},
	{_"Diamond Storm", 95, 100, (pchar*)Diamond_Storm_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[591], &no_procs, &null_mcb},
	{_"Steam Eruption", 95, 110, (pchar*)Steam_Eruption_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[592], &no_procs, &null_mcb},
	{_"Hyperspace Hole", 255, 80, (pchar*)Hyperspace_Hole_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[593], &no_procs, &null_mcb},
	{_"Water Shuriken", 100, 15, (pchar*)Water_Shuriken_desc, 20, 1, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[594], &no_procs, &null_mcb},
	{_"Mystical Fire", 100, 75, (pchar*)Mystical_Fire_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[595], &no_procs, &null_mcb},
	{_"Spiky Shield", 255, 0, (pchar*)Spiky_Shield_desc, 10, 4, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[596], &no_procs, &null_mcb},
	{_"Aromatic Mist", 255, 0, (pchar*)Aromatic_Mist_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[597], &no_procs, &null_mcb},
	{_"Eerie Impulse", 100, 0, (pchar*)Eerie_Impulse_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[598], &no_procs, &null_mcb},
	{_"Venom Drench", 100, 0, (pchar*)Venom_Drench_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[599], &no_procs, &null_mcb},
	{_"Powder", 100, 0, (pchar*)Powder_desc, 20, 1, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[600], &no_procs, &null_mcb},
	{_"Geomancy", 255, 0, (pchar*)Geomancy_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[601], &no_procs, &null_mcb},
	{_"Magnetic Flux", 255, 0, (pchar*)Magnetic_Flux_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[602], &no_procs, &null_mcb},
	{_"Happy Hour", 255, 0, (pchar*)Happy_Hour_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[603], &no_procs, &null_mcb},
	{_"Electric Terrain", 255, 0, (pchar*)Electric_Terrain_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[604], &no_procs, &null_mcb},
	{_"Dazzling Gleam", 100, 80, (pchar*)Dazzling_Gleam_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[605], &no_procs, &null_mcb},
	{_"Celebrate", 255, 0, (pchar*)Celebrate_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[606], &no_procs, &null_mcb},
	{_"Baby-Doll Eyes", 100, 0, (pchar*)Baby_Doll_Eyes_desc, 30, 1, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[607], &no_procs, &null_mcb},
	{_"Nuzzle", 100, 20, (pchar*)Nuzzle_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[608], &no_procs, &null_mcb},
	{_"Hold Back", 100, 40, (pchar*)Hold_Back_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[609], &no_procs, &null_mcb},
	{_"Infestation", 100, 20, (pchar*)Infestation_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[610], &no_procs, &null_mcb},
	{_"Power-Up Punch", 100, 40, (pchar*)Power_Up_Punch_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_FIGHTING, &m_flags[611], &no_procs, &null_mcb},
	{_"Oblivion Wing", 100, 80, (pchar*)Oblivion_Wing_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[612], &no_procs, &null_mcb},
	{_"Thousand Arrows", 100, 90, (pchar*)Thousand_Arrows_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[613], &no_procs, &null_mcb},
	{_"Thousand Waves", 100, 90, (pchar*)Thousand_Waves_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[614], &no_procs, &null_mcb},
	{_"Hold Hands", 255, 0, (pchar*)Hold_Hands_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[615], &no_procs, &null_mcb},
	{_"Land‘s Wrath", 100, 90, (pchar*)Lands_Wrath_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[616], &no_procs, &null_mcb},
	{_"Light of Ruin", 90, 140, (pchar*)Light_of_Ruin_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[617], &no_procs, &null_mcb},
	{_"Origin Pulse", 85, 110, (pchar*)Origin_Pulse_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[618], &no_procs, &null_mcb},
	{_"Precipice Blades", 85, 120, (pchar*)Precipice_Blades_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[619], &no_procs, &null_mcb},
	{_"Dragon Ascent", 100, 120, (pchar*)Dragon_Ascent_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[620], &no_procs, &null_mcb},
	{_"Hyperspace Fury", 255, 100, (pchar*)Hyperspace_Fury_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[621], &no_procs, &null_mcb},
	{_"Shore Up", 255, 0, (pchar*)Shore_Up_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[622], &no_procs, &null_mcb},
	{_"First Impression", 100, 90, (pchar*)First_Impression_desc, 10, 2, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[623], &no_procs, &null_mcb},
	{_"Baneful Bunker", 255, 0, (pchar*)Baneful_Bunker_desc, 10, 4, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[624], &no_procs, &null_mcb},
	{_"Spirit Shackle", 100, 80, (pchar*)Spirit_Shackle_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[625], &no_procs, &null_mcb},
	{_"Darkest Lariat", 100, 85, (pchar*)Darkest_Lariat_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[626], &no_procs, &null_mcb},
	{_"Sparkling Aria", 100, 90, (pchar*)Sparkling_Aria_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[627], &no_procs, &null_mcb},
	{_"Ice Hammer", 90, 100, (pchar*)Ice_Hammer_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[628], &no_procs, &null_mcb},
	{_"Floral Healing", 255, 0, (pchar*)Floral_Healing_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[629], &no_procs, &null_mcb},
	{_"High Horsepower", 95, 95, (pchar*)High_Horsepower_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[630], &no_procs, &null_mcb},
	{_"Strength Sap", 100, 0, (pchar*)Strength_Sap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[631], &no_procs, &null_mcb},
	{_"Solar Blade", 100, 125, (pchar*)Solar_Blade_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[632], &no_procs, &null_mcb},
	{_"Leafage", 100, 40, (pchar*)Leafage_desc, 40, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[633], &no_procs, &null_mcb},
	{_"Spotlight", 255, 0, (pchar*)Spotlight_desc, 15, 3, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[634], &no_procs, &null_mcb},
	{_"Toxic Thread", 100, 0, (pchar*)Toxic_Thread_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[635], &no_procs, &null_mcb},
	{_"Laser Focus", 255, 0, (pchar*)Laser_Focus_desc, 30, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[636], &no_procs, &null_mcb},
	{_"Gear Up", 255, 0, (pchar*)Gear_Up_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[637], &no_procs, &null_mcb},
	{_"Throat Chop", 100, 80, (pchar*)Throat_Chop_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[638], &no_procs, &null_mcb},
	{_"Pollen Puff", 100, 90, (pchar*)Pollen_Puff_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[639], &no_procs, &null_mcb},
	{_"Anchor Shot", 100, 80, (pchar*)Anchor_Shot_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[640], &no_procs, &null_mcb},
	{_"Psychic Terrain", 255, 0, (pchar*)Psychic_Terrain_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[641], &no_procs, &null_mcb},
	{_"Lunge", 100, 80, (pchar*)Lunge_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_BUG, &m_flags[642], &no_procs, &null_mcb},
	{_"Fire Lash", 100, 80, (pchar*)Fire_Lash_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[643], &no_procs, &null_mcb},
	{_"Power Trip", 100, 20, (pchar*)Power_Trip_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[644], &no_procs, &null_mcb},
	{_"Burn Up", 100, 130, (pchar*)Burn_Up_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[645], &no_procs, &null_mcb},
	{_"Speed Swap", 255, 0, (pchar*)Speed_Swap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[646], &no_procs, &null_mcb},
	{_"Smart Strike", 255, 70, (pchar*)Smart_Strike_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[647], &no_procs, &null_mcb},
	{_"Purify", 255, 0, (pchar*)Purify_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_POISON, &m_flags[648], &no_procs, &null_mcb},
	{_"Revelation Dance", 100, 90, (pchar*)Revelation_Dance_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[649], &no_procs, &null_mcb},
	{_"Core Enforcer", 100, 100, (pchar*)Core_Enforcer_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[650], &no_procs, &null_mcb},
	{_"Trop Kick", 100, 70, (pchar*)Trop_Kick_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_GRASS, &m_flags[651], &no_procs, &null_mcb},
	{_"Instruct", 255, 0, (pchar*)Instruct_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[652], &no_procs, &null_mcb},
	{_"Beak Blast", 100, 100, (pchar*)Beak_Blast_desc, 15, -3, 1, MOVE_PHYSICAL, MTYPE_FLYING, &m_flags[653], &no_procs, &null_mcb},
	{_"Clanging Scales", 100, 110, (pchar*)Clanging_Scales_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[654], &no_procs, &null_mcb},
	{_"Dragon Hammer", 100, 90, (pchar*)Dragon_Hammer_desc, 15, 0, 1, MOVE_PHYSICAL, MTYPE_DRAGON, &m_flags[655], &no_procs, &null_mcb},
	{_"Brutal Swing", 100, 60, (pchar*)Brutal_Swing_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_DARK, &m_flags[656], &no_procs, &null_mcb},
	{_"Aurora Veil", 255, 0, (pchar*)Aurora_Veil_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_ICE, &m_flags[657], &no_procs, &null_mcb},
	{_"Shell Trap", 100, 150, (pchar*)Shell_Trap_desc, 5, -3, 1, MOVE_PHYSICAL, MTYPE_FIRE, &m_flags[658], &no_procs, &null_mcb},
	{_"Fleur Cannon", 90, 130, (pchar*)Fleur_Cannon_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[659], &no_procs, &null_mcb},
	{_"Psychic Fangs", 100, 85, (pchar*)Psychic_Fangs_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[660], &no_procs, &null_mcb},
	{_"Stomping Tantrum", 100, 75, (pchar*)Stomping_Tantrum_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GROUND, &m_flags[661], &no_procs, &null_mcb},
	{_"Shadow Bone", 100, 85, (pchar*)Shadow_Bone_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[662], &no_procs, &null_mcb},
	{_"Accelerock", 100, 40, (pchar*)Accelerock_desc, 20, 1, 1, MOVE_PHYSICAL, MTYPE_ROCK, &m_flags[663], &no_procs, &null_mcb},
	{_"Liquidation", 100, 85, (pchar*)Liquidation_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_WATER, &m_flags[664], &no_procs, &null_mcb},
	{_"Prismatic Laser", 100, 160, (pchar*)Prismatic_Laser_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_PSYCHIC, &m_flags[665], &no_procs, &null_mcb},
	{_"Spectral Thief", 100, 90, (pchar*)Spectral_Thief_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[666], &no_procs, &null_mcb},
	{_"Sunsteel Strike", 100, 100, (pchar*)Sunsteel_Strike_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_STEEL, &m_flags[667], &no_procs, &null_mcb},
	{_"Moongeist Beam", 100, 100, (pchar*)Moongeist_Beam_desc, 5, 0, 1, MOVE_PHYSICAL, MTYPE_GHOST, &m_flags[668], &no_procs, &null_mcb},
	{_"Tearful Look", 255, 0, (pchar*)Tearful_Look_desc, 20, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[669], &no_procs, &null_mcb},
	{_"Zing Zap", 100, 80, (pchar*)Zing_Zap_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_ELECTRIC, &m_flags[670], &no_procs, &null_mcb},
	{_"Nature‘s Madness", 90, 0, (pchar*)Natures_Madness_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_FAIRY, &m_flags[671], &no_procs, &null_mcb},
	{_"Multi-Attack", 100, 90, (pchar*)Multi_Attack_desc, 10, 0, 1, MOVE_PHYSICAL, MTYPE_NORMAL, &m_flags[672], &no_procs, &null_mcb},
};
