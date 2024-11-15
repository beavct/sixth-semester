from model import Model_Tabela_Braseileirao
from view import View
from controller import Controller_Tabela

# Instancia as classes
model = Model_Tabela_Braseileirao()
controller = Controller_Tabela()
view = View()

controller.add_match(model, view)