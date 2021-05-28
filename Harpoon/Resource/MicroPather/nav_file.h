#pragma once
#include "nav_area.h"
#include "micropather.h"

namespace nav_mesh {
	class nav_file : public micropather::Graph {
	public:
		nav_file( ) { }
		nav_file( std::string_view nav_mesh_file );
		
		void load( std::string_view nav_mesh_file );

		std::vector< vec3_t > find_path( vec3_t from, vec3_t to );
		std::vector< vec3_t > find_path(vec3_t from, int to_ID);

		//MicroPather implementation
		virtual float LeastCostEstimate( void* start, void* end ) {
			auto& start_area = get_area_by_id( std::uint32_t( start ) );
			auto& end_area = get_area_by_id( std::uint32_t( end ) );
			auto distance = start_area.get_center( ) - end_area.get_center( );

			return std::sqrtf( distance.x * distance.x + distance.y * distance.y + distance.z * distance.z );
		}

		virtual void AdjacentCost( void* state, micropather::MPVector< micropather::StateCost >* adjacent ) {
			auto& area = get_area_by_id( std::uint32_t( state ) );
			auto& area_connections = area.get_connections( );

			for ( auto& connection : area_connections ) {
				auto& connection_area = get_area_by_id( connection.id );
				auto distance = connection_area.get_center( ) - area.get_center( );

				micropather::StateCost cost = { reinterpret_cast< void* >( connection_area.get_id( ) ), 
					std::sqrtf( distance.x * distance.x + distance.y * distance.y + distance.z * distance.z ) };
				
				adjacent->push_back( cost );
			}
		}

		virtual void PrintStateInfo( void* state ) { }

		std::vector<nav_area>* getNavAreas() {
			return &m_areas;
		}



		bool inArea(Vector playerpos, vec3_t currentTarget) {
			vec3_t playerposV;
			playerposV.convertVector(playerpos);
			return (get_area_by_position(playerposV).get_center() == get_area_by_position(currentTarget).get_center());
		}

		bool inArea(Vector playerpos, int ID) {
			vec3_t playerposV;
			playerposV.convertVector(playerpos);
			return (get_area_by_position(playerposV).get_center() == get_area_by_id((uint32_t)ID).get_center());
		}

		uint32_t getAreaID(Vector playerpos) {
			vec3_t playerposV;
			playerposV.convertVector(playerpos);
			return (get_area_by_position(playerposV).get_id());
		}

		Vector nearestArea(Vector CurrPos) {

			Vector Vec{ 0,0,0 };

			for (auto& area : m_areas) {
				if (Vec == Vector{ 0, 0, 0 }) {
					Vec = area.get_center().toVector();
					continue;
				}

				if (Vec.distTo(CurrPos) > area.get_center().toVector().distTo(CurrPos)) {
					Vec = area.get_center().toVector();
				}
			}

			return Vec;
		}


		nav_mesh::nav_area nearestAreaReturnArea(Vector CurrPos) {

			Vector Vec{ 0,0,0 };


			nav_area* area_save = 0;
			for (auto& area : m_areas) {
				if (Vec == Vector{ 0, 0, 0 }) {
					Vec = area.get_center().toVector();
					continue;
				}

				if (Vec.distTo(CurrPos) > area.get_center().toVector().distTo(CurrPos)) {
					Vec = area.get_center().toVector();
					area_save = &area;
				}
			}


			if (area_save) {
				return *area_save;
			}


			throw std::exception("FTFA: nav_files::nearestAreaReturnArea Failed To Return Area");


		}

		nav_mesh::nav_area* nearestAreaReturnAreaPtr(Vector CurrPos) {
			if (m_areas.empty()) {
				throw std::exception("NFE nav_file::get_area_by_position: nav_area (m_areas) empty");
			}

			Vector Vec{ 0,0,0 };


			nav_area* area_save = 0;
			for (auto& area : m_areas) {
				if (Vec == Vector{ 0, 0, 0 }) {
					Vec = area.get_center().toVector();
					continue;
				}

				if (Vec.distTo(CurrPos) > area.get_center().toVector().distTo(CurrPos)) {
					Vec = area.get_center().toVector();
					area_save = &area;
				}
			}


			if (area_save) {
				return area_save;
			}
			else {
				return 0;
			}



		}
		
		nav_area& get_area_by_id(std::uint32_t id);
		nav_area& get_area_by_position(vec3_t position);
		nav_area& get_area_by_position(Vector vPosition);
	private:


		std::unique_ptr< micropather::MicroPather > m_pather = nullptr;

		std::uint8_t m_is_analyzed = 0,
			m_has_unnamed_areas = 0;

		std::uint16_t m_place_count = 0; 

		std::uint32_t m_magic = 0xFEEDFACE, 
			m_version = 0,
			m_sub_version = 0,
			m_source_bsp_size = 0,
			m_area_count = 0;

		nav_buffer m_buffer = { };
		std::vector< nav_area > m_areas = { };
		std::vector< std::string > m_places = { };
	};
}