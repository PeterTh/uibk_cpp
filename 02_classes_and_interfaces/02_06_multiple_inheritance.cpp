#include <vector>

class Collider { };

class Sprite { };

class AnimatedSprite : public Sprite {
  public:
	void advanceTime(double deltaT) {
		/* ... */
	}
};

class SoundEmitter { };

class Controlled { };

class AIRoutine { };

class Pickup : public AnimatedSprite, public SoundEmitter { };

class Wall : public Collider, public Sprite { };

class Lifeform : public Collider, public AnimatedSprite, public SoundEmitter { };

class Player : public Lifeform, public Controlled { };

class Enemy : public Lifeform, public AIRoutine { };

// Notes:
// Multiple inheritance can be useful, especially for interfaces.
// For implementation, *think about whether composition could solve the same problem*

// Advantage of multiple inheritance: can be used to store all types conforming to one interface in containers
void resolveCollisions(std::vector<Collider*> colliders) {
	/* ... */
}

void advanceTime(double deltaT, std::vector<AnimatedSprite*> sprites) {
	for(auto sprite : sprites) {
		sprite->advanceTime(deltaT);
	}
}
