from RoutesCenter import RoutesCenter
import pickle


class Interface(object):
    def __init__(self):
        self.command = ""
        self.string_arguments = []
        self.numeric_arguments = []
        self.RoutesCenter = RoutesCenter()

    def load_routes_center(self):
        with open('data.pickle', 'rb') as f:
            self.RoutesCenter = pickle.load(f)

    def save_routes_center(self):
        with open('data.pickle', 'wb') as f:
            pickle.dump(self.RoutesCenter, f)

    def get_command(self):
        self.clear_arguments()
        self.command = ""
        self.command = input("Enter command: ")
        if self.command == "exit":
            return False
        return True


    def get_id(self):
        while (True):
            id_argument = input("Enter unique ID: ")
            if id_argument == "return":
                return False
            if not id_argument.isdecimal():
                print("ID has to be int")
                continue
            if self.RoutesCenter.valid_id(int(id_argument)):
                self.numeric_arguments.append(int(id_argument));
                return True
            else:
                print("Not unique ID. Try again. ")

    def get_city(self, city1, first_input):
        if first_input:
            self.string_arguments.append(input("Enter city 1: "))
            return True
        else:
            while(True):
                text = input("Enter city 2: ")
                if text == "return":
                    return False
                if self.string_arguments[0] != text:
                    self.string_arguments.append(text)
                    return True
                else:
                    print("City 2 has to be different from city 1. Try again. ")

    def get_bus_info(self, info_string):
        if info_string == "return":
            return False
        if info_string == "color":
            color = input("Enter bus color: ")
            self.string_arguments.append(color)
            return True
        if info_string == "mark":
            mark = input("Enter bus mark: ")
            self.string_arguments.append(mark)
            return True

    def get_route_id(self):
        while(True):
            id_argument = input("Enter route ID: ")
            if id_argument == "return":
                return False
            if not id_argument.isdecimal():
                print("ID has to be int")
                continue
            if self.RoutesCenter.route_list.exists(int(id_argument)):
                self.numeric_arguments.append(int(id_argument))
                return True
            else:
                print("There is no such route. Enter an existing route ID. ")

    def get_bus_id(self):
        while(True):
            id_argument = input("Enter bus ID: ")
            if id_argument == "return":
                return False
            if not id_argument.isdecimal():
                print("ID has to be int")
                continue
            if self.RoutesCenter.bus_list.exists(int(id_argument)):
                self.numeric_arguments.append(int(id_argument))
                return True
            else:
                print("There is no such bus. Enter an existing bus ID. ")

    def clear_arguments(self):
        self.numeric_arguments.clear()
        self.string_arguments.clear()

    def recognize_command(self):
        if self.command == "add route":
            if not self.get_id(): return
            if not self.get_city(-1, True): return
            if not self.get_city(self.string_arguments[0], False): return
            self.RoutesCenter.add_route(self.numeric_arguments[0], self.string_arguments[0], self.string_arguments[1])
        if self.command == "add bus":
            if not self.get_id(): return
            if not self.get_route_id(): return
            if not self.get_bus_info("color"): return
            if not self.get_bus_info("mark"): return
            self.RoutesCenter.add_bus(self.numeric_arguments[0], self.numeric_arguments[1],
                                      self.string_arguments[0], self.string_arguments[1])
        if self.command == "delete bus":
            if not self.get_bus_id(): return
            self.RoutesCenter.delete_bus(self.numeric_arguments[0])
        if self.command == "delete route":
            if not self.get_route_id(): return
            self.RoutesCenter.delete_route(self.numeric_arguments[0])
        if self.command == "reassign bus":
            if not self.get_bus_id(): return
            if not self.get_route_id(): return
            self.RoutesCenter.reassign_bus(self.numeric_arguments[0], self.numeric_arguments[1])
        if self.command == "modify bus":
            if not self.get_bus_id(): return
            print(self.RoutesCenter.bus_list.get_by_id(self.numeric_arguments[0]))
            if not self.get_bus_info("color"): return
            if not self.get_bus_info("mark"): return
            self.RoutesCenter.modify_bus(self.numeric_arguments[0], self.string_arguments[0], self.string_arguments[1])
        if self.command == "modify root":
            if not self.get_route_id(): return
            print(self.RoutesCenter.route_list.get_route_by_id(self.numeric_arguments[0]))
            if not self.get_city(-1, True): return
            if not self.get_city(self.string_arguments[0], False): return
            self.RoutesCenter.modify_root(self.numeric_arguments[0], self.string_arguments[0], self.string_arguments[1])
        if self.command == "filter buses by city":
            if not self.get_city(-1, True): return
            print(self.RoutesCenter.get_buses_by_city(self.string_arguments[0]))
        if self.command == "print":
            print(self.RoutesCenter)
        if self.command == "print buses":
            print(self.RoutesCenter.bus_list)
        if self.command == "print routes":
            print(self.RoutesCenter.route_list)



