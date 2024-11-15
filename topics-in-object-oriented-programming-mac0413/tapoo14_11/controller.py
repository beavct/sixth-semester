from model import Model_Tabela_Braseileirao
from view import View, View_Tabela, View_Tweets

class Controller_Tabela:
    def __init__(self):
        pass

    def add_match(self, model, view):
        while True:
            team_name_1 = input("1o time: ")
            goals_team_1 = int(input(f"Gols do {team_name_1}: "))

            team_name_2 = input("2o time: ")
            goals_team_2 = int(input(f"Gols do {team_name_2}: "))

            tipo = int(input("(1) Tweet ou (2) Tabela: "))

            print("\n")

            if tipo == 1:
                view.set_strategy(View_Tweets())
            else:
                view.set_strategy(View_Tabela())

            model.match(team_name_1, team_name_2, goals_team_1, goals_team_2, view)