using EntityId = int;

class Entity {

private:
	std::string name;
	EntityId id;

public:
	explicit Entity(EntityId id) :
	name("John"), id(id)
	{}

	const std::string& getName() const { return name; }
	void setName(const std::string& n) { name = n; }
	EntityId getId() const { return id; }

};



class EntityManager {

private:
	std::unordered_map<EntityId, std::unique_ptr<Entity>> entities;
	EntityId idCounter;
	sol::state &lua;

public: 
	EntityManager(sol::state &lua) : idCounter(0), lua(lua) {}

	Entity& createEntity() {
		auto id = idCounter;
		++idCounter;

		auto inserted = entities.emplace(id, std::make_unique<Entity>(id));
		auto it = inserted.first; // iterator to created id/Entity pair
		auto& e = *it->second; // created entity
		lua["createHandle"](e);
		return e;
	}

	void removeEntity(EntityId id) {
		lua["onEntityRemoved"](id);
		entities.erase(id);
	}

};

