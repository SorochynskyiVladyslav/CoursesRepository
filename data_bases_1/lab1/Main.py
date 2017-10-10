from Interface import Interface
from RoutesCenter import RoutesCenter
import pickle

"""
routes_center = RoutesCenter()
routes_center.add_route(1421, "Kyiv", "Lviv")
routes_center.add_route(1422, "Odessa", "Lviv")
routes_center.add_route(1423, "Kyiv", "Odessa")
routes_center.add_route(1424, "Chernigiv", "Lviv")

routes_center.add_bus(2131, 1421, "Yellow", "Bogdan")
routes_center.add_bus(2132, 1421, "Red", "Citroen")
routes_center.add_bus(2133, 1422, "Yellow", "Bogdan")
routes_center.add_bus(2134, 1422, "Black", "Mercedez")
routes_center.add_bus(2135, 1423, "White", "Bogdan")
routes_center.add_bus(2136, 1423, "Purple", "Mazda")
routes_center.add_bus(2137, 1424, "Green", "Volkswagen")
routes_center.add_bus(2138, 1424, "White", "Citroen")
"""

interface = Interface()
interface.load_routes_center()

while (True):
    if not interface.get_command():
        break
    interface.recognize_command()

interface.save_routes_center()


