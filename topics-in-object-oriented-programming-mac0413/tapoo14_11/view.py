class View:
    def __init__(self, strategy=None):
        self.strategy = strategy

    def set_strategy(self, strategy):
        self.strategy = strategy

    def display(self, data):
        if self.strategy:
            self.strategy.display(data) 
        else:
            print("Nenhuma estratégia foi setada")

class View_Tabela(View):
    def __init_(self):
        super().__init__()

    def display(self, data):
            # Formatação
            print(f"{"Time":<10}{"P":<6}{"J":<6}{"V":<6}{"E":<6}{"D":<6}{"GP":<6}{"GC":<6}{"SG":<6}")
            
            sorted_teams = sorted(data.values(), key=lambda t: (t.team_data["P"], t.team_data["SG"]), reverse=True)

            
            for team in sorted_teams:
                team_data = team.team_data
                # Formatação
                print(f"{team_data["team_name"]:<10}{team_data["P"]:<6}{team_data["V"] + team_data["E"] + team_data["D"]:<6}"
                    f"{team_data["V"]:<6}{team_data["E"]:<6}{team_data["D"]:<6}{team_data["GP"]:<6}{team_data["GC"]:<6}"
                    f"{team_data["SG"]:<6}")
            
            print("\n")


class View_Tweets(View):
    def __init_(self):
        super().__init__()

    def display(self, data):
         # data é do tipo lista: [nome do time ganhador, nome do time perdedor, gols do time ganhador, ....]
        if data[1] == data[3]:
            print(f"{data[0]} e {data[2]} empataram com {data[1]} gols cada\n")
        elif data[1] > data[3]:
            print(f"O {data[0]} venceu o {data[2]} por {data[1]} a {data[3]}\n")
        else:
            print(f"O {data[2]} venceu o {data[0]} por {data[3]} a {data[1]}\n")
            