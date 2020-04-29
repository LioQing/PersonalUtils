#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <array>
#include <vector>
#include <bitset>
#include <queue>

// unit of time of difference in time between the previous fame the next frame
// to be passed into systems
// can be ignored if not used
typedef uint32_t DeltaTime;

namespace lecs
{
	// max number of log stored
	constexpr std::size_t MAX_LOG = 32;

	// max number of component
	// change if needed
	constexpr std::size_t MAX_COMPONENT = 32;

	// tags for logs
	// optionally add custom tags
	enum LogTag
	{
		LT_COMPONENT,
		LT_ENTITY,
		LT_SYSTEM,
		LT_ERROR,
		LT_CREATE,
		LT_DELETE,
		LT_EVENT,
		LT_WARNING,
		LT_DEBUG,

		LT_SIZE
	};

	// logger class for storing logs and log related functions
	class Logger
	{
	public:

		// add log
		template <typename... T>
		void add_log(std::string log_msg, T... tag)
		{
			LogTag tags[] = { tag... };
			std::pair<std::bitset<n_tag>, std::string> log;

			bool shown = false;
			log.second = log_msg;
			for (auto t : tags)
			{
				log.first[t] = true;
				log_per_tag[t] = log_msg;

				if (show[t] && !shown)
				{
					std::cout << log_msg << std::endl;
					shown = true;
				}
			}

			logs.push_front(log);

			if (logs.size() > MAX_LOG) logs.pop_back();
		}

		// get the previous n amount of log in string
		// default n = max number of log
		std::string get_logs(std::size_t n = MAX_LOG)
		{
			std::string log_msg = "";
			std::size_t begin = n > logs.size() ? logs.size() : n;
			for (std::size_t i = begin; i >= 1; --i)
			{
				log_msg += logs.at(i - 1).second + "\n";
			}
			return log_msg;
		}

		// get the lattest log
		std::string get_log()
		{
			return logs.front().second;
		}

		// get the lattest log with tag
		std::string get_log(LogTag tag)
		{
			return log_per_tag[tag];
		}

		// toggle to turn on or off always output new log to console
		void always_show(bool always = true)
		{
			if (always) show.set();
			else show.reset();
		}

		// same as previous function
		// pass in tags of log(s) that will always be outputted
		template <typename... T>
		void always_show(bool always, T... tag)
		{
			LogTag tags[] = { tag... };
			for (auto t : tags) show.set(t, always);
		}

	private:

		static const std::size_t n_tag = LT_SIZE;

		std::bitset<n_tag> show;
		std::deque<std::pair<std::bitset<n_tag>, std::string>> logs;
		std::array<std::string, n_tag> log_per_tag;
	};

	// the logger used in namespace lecs
	Logger logger;

	// base class for all components
	class Component
	{
	public:

		// store the id of the entity this component belongs to
		uint32_t entity;
	};

	// the next component id to be assigned
	uint32_t next_component_id = 0;

	// get the component id of component T
	// create a new component id if the component type is never assigned an id before
	template <typename T>
	inline uint32_t get_component_type_id()
	{
		static uint32_t id = next_component_id++;

		if (id > MAX_COMPONENT) logger.add_log
		(
			"Error: new component id for Component " + std::string(typeid(T).name()) + " exceed MAX_COMPONENT", 
			LT_ERROR
		);

		return id;
	}

	class EntityManager;

	// entity class to store its own components and id
	class Entity
	{
	private:

		EntityManager& entity_manager;
		bool active = true;

		std::array<std::unique_ptr<Component>, MAX_COMPONENT> components;
		std::bitset<MAX_COMPONENT> component_bitset;

	public:

		// entity id
		uint32_t id;

		Entity(EntityManager& entity_manager, uint32_t id) : entity_manager(entity_manager), id(id) {}

		// check if the entity is active
		bool is_active()
		{
			return active;
		}

		// destroy the entity
		// immediate = false, destroy until the next update of entity manager
		void destroy(bool immediate = false);

		// add component T to this entity
		// pass in unique_ptr type
		template <typename T>
		T& add_component(std::unique_ptr<T> u_ptr)
		{
			u_ptr->entity = id;

			components[get_component_type_id<T>()] = std::move(u_ptr);
			component_bitset[get_component_type_id<T>()] = true;

			logger.add_log
			(
				"New component added to entity: Component " + std::string(typeid(T).name()) + " added to Entity " + std::to_string(id),
				LT_COMPONENT, LT_CREATE
			);
			return *u_ptr.get();
		}

		// pass in component
		template <typename T>
		T& add_component(const T& c)
		{
			c->entity = id;
			std::unique_ptr<Component> u_ptr{ c };

			components[get_component_type_id<T>()] = std::move(u_ptr);
			component_bitset[get_component_type_id<T>()] = true;

			logger.add_log
			(
				"New component added to entity: Component " + std::string(typeid(T).name()) + " added to Entity " + std::to_string(id),
				LT_COMPONENT, LT_CREATE
			);
			return *c;
		}

		// pass in contructor argument of component
		template <typename T, typename... TArgs>
		T& add_component(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = id;
			std::unique_ptr<Component> u_ptr{ c };

			components[get_component_type_id<T>()] = std::move(u_ptr);
			component_bitset[get_component_type_id<T>()] = true;

			logger.add_log
			(
				"New component added to entity: Component " + std::string(typeid(T).name()) + " added to Entity " + std::to_string(id),
				LT_COMPONENT, LT_CREATE
			);
			return *c;
		}

		// remove component T from this entity
		template <typename T>
		T& remove_component()
		{
			T c = *static_cast<T*>(components[get_component_type_id<T>()].get());
			delete components[get_component_type_id<T>()].release();
			component_bitset[get_component_type_id<T>()] = false;

			logger.add_log
			(
				"Component removed from entity: Component " + std::string(typeid(T).name()) + " removed from Entity " + std::to_string(id),
				LT_COMPONENT, LT_DELETE
			);
			return c;
		}

		// get component T from this entity
		template <typename T>
		T& get_component() const
		{
			auto ptr(components[get_component_type_id<T>()].get());
			if (ptr == nullptr) logger.add_log
			(
				"Warning: Entity " + std::to_string(id) + " does not have Component " + std::string(typeid(T).name()) + ", returned nullptr", 
				LT_WARNING
			);
			return *static_cast<T*>(ptr);
		}

		// check whether this entity has component T
		template <typename T>
		bool has_component()
		{
			return component_bitset[get_component_type_id<T>()];
		}
	};

	// entity container class for storing and filtering multiple entities
	class EntityContainer
	{
	private:

		EntityManager& entity_manager;

	public:

		// a vector of entity that contains the entities this container contains
		std::vector<Entity*> entities;

		explicit EntityContainer(EntityManager& entity_manager) : entity_manager(entity_manager) {}

		// get an entity container that only contains entities with component T
		template <typename T>
		EntityContainer entity_filter();
	};

	// entity manager class for managing all entities
	class EntityManager
	{
	private:

		uint32_t next_id;

	public:

		// unique_ptr of entities currently active
		// unsafe to directly get entities through this vector as there will be nullptr
		std::vector<std::unique_ptr<Entity>> entities;

		// vector of id of destroyed entities to be reused
		std::vector<uint32_t> empty_id;

		// check and destroy non active entities
		void update()
		{
			for (auto& e : entities)
			{
				if (!e) continue;
				if (!e->is_active())
				{
					empty_id.push_back(e->id);
					delete e.release();

					logger.add_log
					(
						"Entity destroyed: Entity " + std::to_string(e->id) + " destroyed",
						LT_ENTITY, LT_DELETE
					);
				}
			}
		}

		// immediately destroy the entity
		void immediate_destroy(uint32_t id)
		{
			empty_id.push_back(id);
			delete entities.at(id).release();

			logger.add_log
			(
				"Entity destroyed: Entity " + std::to_string(id) + " destroyed",
				LT_ENTITY, LT_DELETE
			);
		}

		// add entity
		// return reference to the entity
		Entity& add_entity()
		{
			uint32_t new_id;
			bool is_empty = empty_id.empty();
			if (!is_empty)
			{
				new_id = empty_id.back();
				empty_id.pop_back();
			}
			else
			{
				new_id = next_id++;
			}

			Entity* e(new Entity(*this, new_id));
			std::unique_ptr<Entity> u_ptr{ e };
			if (is_empty) entities.resize(entities.size() + 1);
			entities.at(e->id) = std::move(u_ptr);

			logger.add_log
			(
				"Entity created: Entity " + std::to_string(e->id) + " created",
				LT_ENTITY, LT_CREATE
			);
			return *e;
		}

		// get an entity container that contains all the entities active
		// safe to use compare to the vector of entities
		EntityContainer entity_filter()
		{
			EntityContainer en = EntityContainer(*this);
			for (auto& e : entities)
			{
				if (!e) continue;
				en.entities.emplace_back(entities.at(e->id).get());
			}
			return en;
		}

		// get an entity container that only contains entities with component T
		template <typename T>
		EntityContainer entity_filter()
		{
			EntityContainer entities_with = EntityContainer(*this);
			for (auto& e : entities)
			{
				if (!e) continue;
				uint32_t id = e->id;
				if (e->has_component<T>()) entities_with.entities.emplace_back(entities.at(id).get());
			}
			return entities_with;
		}
	};

	// destroy the entity
		// immediate = false, destroy until the next update of entity manager
	void Entity::destroy(bool immediate)
	{
		active = false;
		if (immediate) entity_manager.immediate_destroy(id);
	}

	// get an entity container that only contains entities with component T
	template <typename T>
	EntityContainer EntityContainer::entity_filter()
	{
		{
			EntityContainer entities_with = EntityContainer(entity_manager);
			for (auto& e : entities)
			{
				if (!e) continue;
				uint32_t id = e->id;
				if (e->has_component<T>()) entities_with.entities.emplace_back(entity_manager.entities.at(id).get());
			}
			return entities_with;
		}
	}

	class Event;
	class EventManager;

	// base event subscriber class for all class that will subscribe to events
	class EventSubscriber
	{
	public:

		// vector of id of subscribed event
		std::vector<uint32_t> subscribed;

		// receive function to be called when an subscribed event is emitted
		virtual void receive(Event&) {}
	};

	// base event class for all event class
	class Event
	{
	private:

		EventManager* event_manager;

	public:

		// event id of this event
		uint32_t id;

		// vector of subscribers to this event
		std::vector<EventSubscriber*> subscribers;

		// downcast this event to derived event class
		template <typename T>
		T& downcast()
		{
			return static_cast<T&>(*this);
		}

		// check whether this is of derived event class T
		template <typename T>
		bool is_event() const;
	};

	// event manager class to manage all event
	class EventManager
	{
	private:

		EntityManager* entity_manager;
		uint32_t next_event_id = 0;

	public:

		// vector of events
		std::vector<std::unique_ptr<Event>> events;

		EventManager() : entity_manager(nullptr) {}
		explicit EventManager(EntityManager* entity_manager) : entity_manager(entity_manager) {}

		// get the event id
		// create a new event id if the event type is never assigned an id before
		template <typename T>
		inline uint32_t get_event_id()
		{
			static uint32_t id = next_event_id++;
			return id;
		}

		// unsubscribe an event from a subscriber
		template <typename T>
		void unsubscribe(EventSubscriber* subscriber)
		{
			add_event<T>();
			uint32_t id = get_event_id<T>();
			events.at(id)->subscribers.erase(std::remove_if(
				events.at(id)->subscribers.begin(), events.at(id)->subscribers.end(),
				[subscriber](EventSubscriber* s)
				{
					return s == subscriber;
				}),
				events.at(id)->subscribers.end());

			std::vector<uint32_t>* subscribed = &subscriber->subscribed;
			subscribed->erase(std::remove_if(subscribed->begin(), subscribed->end(),
				[id](const uint32_t& eID)
				{
					return eID == id;
				}),
				subscribed->end());
		}

		// subscribe event T from subscriber
		template <typename T>
		void subscribe(EventSubscriber* subscriber)
		{
			add_event<T>();
			events.at(get_event_id<T>())->subscribers.emplace_back(subscriber);
			subscriber->subscribed.emplace_back(get_event_id<T>());
		}

		// emit event T to all subscriber of that event
		// pass in aArgs to constructor of event T
		template <typename T, typename... TArgs>
		void emit(TArgs... aArgs)
		{
			add_event<T>();
			for (auto& sub : events.at(get_event_id<T>())->subscribers)
			{
				T ev(T(std::forward<TArgs>(aArgs)...));
				ev.event_manager = this;
				ev.id = get_event_id<T>();
				sub->receive(ev);
			}

			logger.add_log
			(
				"Event emitted: Event " + std::string(typeid(T).name()) + " emitted",
				LT_EVENT
			);
		}

		// add event type T
		template <typename T>
		bool add_event()
		{
			if (get_event_id<T>() < events.size()) return false;
			T* ev(new T());
			ev->id = get_event_id<T>();
			std::unique_ptr<T> u_ptr{ ev };
			events.resize(events.size() + 1);
			events.at(ev->id) = std::move(u_ptr);

			logger.add_log
			(
				"Event created: Event " + std::string(typeid(T).name()) + " created",
				LT_EVENT, LT_CREATE
			);

			return true;
		}
	};

	// check whether this is of derived event class T
	template <typename T>
	bool Event::is_event() const
	{
		return id == event_manager->get_event_id<T>();
	}

	// base system class for all system classes
	class System
	{
	public:

		// function to be called everytime system manager is updated
		virtual void update(EntityManager*, EventManager*, DeltaTime) {}
	};

	// system manager class to manager all systems
	class SystemManager
	{
	private:

		EntityManager* entity_manager;
		EventManager* event_manager;

	public:

		// vector of systems
		std::vector<std::unique_ptr<System>> systems;

		SystemManager() : entity_manager(nullptr), event_manager(nullptr) {}
		explicit SystemManager(EntityManager* entity_manager, EventManager* event_manager)
			: entity_manager(entity_manager), event_manager(event_manager) {}

		// add system of class T
		// pass in reference of T
		template <typename T>
		T& add_system(const T& s)
		{
			std::unique_ptr<System> u_ptr{ s };
			systems.emplace_back(std::move(u_ptr));

			logger.add_log
			(
				"System created: System " + std::string(typeid(T).name()) + " created",
				LT_SYSTEM, LT_CREATE
			);
			return *s;
		}

		// pass in unique_ptr of T
		template <typename T>
		T& add_system(std::unique_ptr<T> u_ptr)
		{
			systems.emplace_back(std::move(u_ptr));

			logger.add_log
			(
				"System created: System " + std::string(typeid(T).name()) + " created",
				LT_SYSTEM, LT_CREATE
			);
			return *u_ptr.get();
		}

		// pass in constructor arguments of T
		template <typename T, typename... TArgs>
		T& add_system(TArgs&&... aArgs)
		{
			T* s(new T(std::forward<TArgs>(aArgs)...));
			std::unique_ptr<System> u_ptr{ s };
			systems.emplace_back(std::move(u_ptr));

			logger.add_log
			(
				"System created: System " + std::string(typeid(T).name()) + " created",
				LT_SYSTEM, LT_CREATE
			);
			return *s;
		}

		// update all systems
		void update(DeltaTime delta_time)
		{
			for (auto& s : systems)
			{
				s->update(entity_manager, event_manager, delta_time);
			}
		}
	};

	// ecs managers class to store all managers
	// optional to be used
	class ECSManagers
	{
	public:

		EntityManager entity_manager;
		SystemManager system_manager;
		EventManager event_manager;

		ECSManagers()
		{
			entity_manager = EntityManager();
			event_manager = EventManager(&entity_manager);
			system_manager = SystemManager(&entity_manager, &event_manager);
		}

		// update all ecs managers
		void update_ecs_managers(DeltaTime delta_time = NULL)
		{
			entity_manager.update();
			system_manager.update(delta_time);
		}
	};
}
