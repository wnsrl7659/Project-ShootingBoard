#include "SoundEventHandler.h"
#include "SoundSystem.h"


void PlayerShootSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/PlayerShoot");
  SoundSystem::Get()->PlayFmodSound(index);
}
void PlayerRapidShootSound() {
  static unsigned index =
    SoundSystem::Get()->GetSoundEventIndex("event:/Game/RapidFire");
  SoundSystem::Get()->PlayFmodSound(index);
}
void ShotHitSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/ShotHit");
  SoundSystem::Get()->PlayFmodSound(index);
}
void DebrisSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/Debris");
  SoundSystem::Get()->PlayFmodSound(index);
}
void FlagPickupSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/FlagPickup");
  SoundSystem::Get()->PlayFmodSound(index);
}
void FlagDropSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/FlagDrop");
  SoundSystem::Get()->PlayFmodSound(index);
}
void PlayerWinSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/PlayerWin");
  SoundSystem::Get()->PlayFmodSound(index);
}
void ButtonSelectSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Menu/ButtonSelect");
  SoundSystem::Get()->PlayFmodSound(index);
}
void ButtonNavigationSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Menu/ButtonNavigate");
  SoundSystem::Get()->PlayFmodSound(index);
}
void ExplosionSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/Explosion");
  SoundSystem::Get()->PlayFmodSound(index);
}
void FeulFullSound() {
  static unsigned index =
    SoundSystem::Get()->GetSoundEventIndex("event:/Game/FeulFull");
  SoundSystem::Get()->PlayFmodSound(index);
}
void FeulemptySound() {
  static unsigned index =
    SoundSystem::Get()->GetSoundEventIndex("event:/Game/FuelEmpty");
  SoundSystem::Get()->PlayFmodSound(index);
}
void SrartRefuelSound() {
  static unsigned index =
    SoundSystem::Get()->GetSoundEventIndex("event:/Game/Refuel");
  FMOD::Studio::EventInstance* inst = SoundSystem::Get()->PlayFmodSound(index);
  
  // set the parameter on the instance
  //inst->setParameterByName("feul", *(float*)data);
}
void PaintSound() {
  static unsigned index =
    SoundSystem::Get()->GetSoundEventIndex("event:/Game/Paint");
  FMOD::Studio::EventInstance* inst = SoundSystem::Get()->PlayFmodSound(index);
}

void StartScoreCounterSound() {
  static unsigned index =
    SoundSystem::Get()->GetSoundEventIndex("event:/Game/ScoreCounter");
  SoundSystem::Get()->StartLoopingSound(index, reinterpret_cast<float*>(0));
}
void EndScoreCounterSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/ScoreCounter");
  SoundSystem::Get()->EndLoopingSound(index);
}
void StartPlayerMoveSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/PlayerMove");
  SoundSystem::Get()->StartLoopingSound(index, reinterpret_cast<float*>(0));
}
void EndPlayerMoveSound() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Game/PlayerMove");
  SoundSystem::Get()->EndLoopingSound(index);
}
void StartGameMusic() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Music/GameMusic");
  SoundSystem::Get()->StartLoopingSound(index, reinterpret_cast<float*>(0));
}
void EndGameMusic() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Music/GameMusic");
  SoundSystem::Get()->EndLoopingSound(index);
}
void StartMenuMusic() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Music/MenuMusic");
  SoundSystem::Get()->StartLoopingSound(index, reinterpret_cast<float*>(0));
}
void EndMenuMusic() {
  static unsigned index =
  SoundSystem::Get()->GetSoundEventIndex("event:/Music/MenuMusic");
  SoundSystem::Get()->EndLoopingSound(index);
}
