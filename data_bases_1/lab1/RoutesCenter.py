from Bus import Buses
from Bus import Bus
from Route import Routes
from Route import Route


class RoutesCenter(object):
    def __init__(self):
        self.bus_list = Buses()
        self.route_list = Routes()

    def valid_id(self, id_argument):
        if Buses.exists(id_argument):
            return False
        if Routes.exists(id_argument):
            return False
        return True

    def add_bus(self, bus_id, route_id, color, mark):
        if self.bus_list.exists(bus_id):
            return
        if not self.route_list.exists(route_id):
            return
        self.bus_list.add(Bus(bus_id, color, mark))
        self.route_list.add_bus(route_id, bus_id)

    def add_route(self, route_id, city1, city2):
        if self.route_list.exists(route_id):
            return
        self.route_list.add(Route(city1, city2, route_id))

    def delete_bus(self, bus_id):
        self.bus_list.delete(bus_id)
        self.route_list.delete_bus(bus_id)

    def delete_route(self, route_id):
        target_route = self.route_list.get_route_by_id(route_id)
        if len(target_route.get_buses) == 0:
            self.route_list.delete(route_id)
        else:
            print("Can't delete a route with buses")
            return

    def reassign_bus(self, bus_id, new_route_id):
        self.route_list.delete_bus(bus_id)
        self.route_list.add_bus(new_route_id, bus_id)

    def modify_bus(self, bus_id, new_color, new_mark):
        self.bus_list.modify_bus(bus_id, new_color, new_mark)

    def modify_root(self, route_id, new_city1, new_city2):
        self.route_list.modify_root(route_id, new_city1, new_city2)

    def get_buses_by_city(self, city):
        target_routes = self.route_list.get_route_by_city(city);
        if len(target_routes) == 0:
            return False
        result_buses_id = []
        result_buses = Buses()
        for route in target_routes:
            result_buses_id.extend(route.get_buses())
        for bus_id in result_buses_id:
            result_buses.add(self.bus_list.get_by_id(bus_id))
        return result_buses

    def __str__(self):
        string = "Routes center:"
        for route in self.route_list.get_routes():
            string = string + "\n " + str (route)
            for bus in self.bus_list.get_buses():
                if route.bus_exists(bus.id):
                    string = string + "\n  " + str(bus)
        return string


