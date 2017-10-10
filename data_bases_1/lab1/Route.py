class Route(object):
    def __init__(self, city1, city2, route_id):
        self.city1 = city1
        self.city2 = city2
        self.id = route_id
        self.buses_id = []

    def get_buses(self):
        return self.buses_id

    def add_bus(self, bus_id):
        self.buses_id.append(bus_id);

    def delete_bus(self, bus_id):
        ind = -1
        for bus in self.buses_id:
            ind += 1
            if bus == bus_id:
                self.buses_id.pop(ind)
                return

    def bus_exists(self, bus_id):
        for bus in self.buses_id:
            if bus == bus_id:
                return True
        return False

    def __str__(self):
        return "Route id=%d: %s<---->%s" % (self.id, self.city1, self.city2)


class Routes(object):
    def __init__(self):
        self.routes = []

    def add(self, route):
        self.routes.append(route)

    def delete(self, id):
        ind = -1
        for route in self.routes:
            ind += 1
            if route.id == id:
                self.routes.pop(ind)
                return

    def add_bus(self, route_id, bus_id):
        for route in self.routes:
            if route.id == route_id:
                route.add_bus(bus_id)

    def delete_bus(self, bus_id):
        for route in self.routes:
            route.delete_bus(bus_id)

    def delete_bus(self, route_id, bus_id):
        for route in self.routes:
            if route.id == route_id:
                route.delete_bus(bus_id)
                return

    def exists(self, id):
        for route in self.routes:
            if id == route.id:
                return True
        return False

    def bus_exists(self, bus_id):
        for route in self.routes:
            if route.bus_exists(bus_id):
                return True
        return False

    def get_route_by_id(self, route_id):
        for route in self.routes:
            if route.id == route_id:
                return route

    def modify_root(self, route_id, new_city1, new_city2):
        for route in self.routes:
            if route.id == route_id:
                route.city1 = new_city1
                route.city2 = new_city2
                return

    def get_route_by_city(self, city):
        result_routes = []
        for route in self.routes:
            if route.city1 == city or route.city2 == route:
                result_routes.append(route)
        return result_routes

    def get_routes(self):
        return self.routes

    def __str__(self):
        return "\n".join(str(route) for route in self.routes)