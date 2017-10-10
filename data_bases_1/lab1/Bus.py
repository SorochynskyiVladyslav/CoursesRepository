class Bus(object):
    def __init__(self, bus_id, color, mark):
        self.id = bus_id
        self.color = color
        self.mark = mark

    def __str__(self):
        return "Bus id=%d: %s %s" % (self.id, self.color, self.mark)


class Buses(object):
    def __init__(self):
        self.buses = []

    def add(self, bus):
        self.buses.append(bus)

    def delete(self, id):
        ind = -1
        for bus in self.buses:
            ind += 1
            if bus.id == id:
                self.buses.pop(ind)
                return

    def exists(self, id):
        for bus in self.buses:
            if id == bus.id:
                return True
        return False

    def get_by_id(self, bus_id):
        if self.exists(bus_id):
            for bus in self.buses:
                if bus.id == bus_id:
                    return bus

    def get_buses(self):
        return self.buses

    def modify_bus(self, bus_id, new_color, new_mark):
        if self.exists(bus_id):
            for bus in self.buses:
                if bus.id == bus_id:
                    bus.color = new_color
                    bus.mark = new_mark
                    return

    def __str__(self):
        return "\n".join(str(bus) for bus in self.buses)