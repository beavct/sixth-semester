from view import View, View_Tabela, View_Tweets

# DICIONÁRIO DE CADA TIME
class Team:
    def __init__(self, team_name):
        self.team_data = {"team_name": team_name,
                          "V": 0, # vitórias 
                          "E": 0, # empates
                          "D": 0, # derrotas
                          "GP": 0, # gols pró
                          "GC": 0, # gols contra
                          "SG": 0, # saldo de gols
                          "P": 0} # pontos

    def increment_V(self):
        self.team_data["V"]+=1        

    def increment_E(self):
        self.team_data["E"]+=1

    def increment_D(self):
        self.team_data["D"]+=1
    
    def add_points(self, value):
        self.team_data["P"]+=value

    def update_goals(self, GP, GC):
        self.team_data["GP"]+=GP
        self.team_data["GC"]+=GC
        self.team_data["SG"]+=(GP-GC)


# TABELA CONTENDO TODOS OS TIMES
class Model_Tabela_Braseileirao:
    def __init__(self):
        self.tabela = {}

    def match(self, team_name_1, team_name_2, team_goals_1, team_goals_2, view):
        data_team_1 = self.find(team_name_1)
        data_team_2 = self.find(team_name_2)

        if team_goals_1 == team_goals_2:
            data_team_1.increment_E()
            data_team_2.increment_E()

            data_team_1.add_points(1)
            data_team_2.add_points(1)

        elif  team_goals_1 > team_goals_2:
            data_team_1.increment_V()
            data_team_2.increment_D()

            data_team_1.add_points(3)

        else:
            data_team_1.increment_D()
            data_team_2.increment_V()

            data_team_2.add_points(3)

        data_team_1.update_goals(team_goals_1, team_goals_2)
        data_team_2.update_goals(team_goals_2, team_goals_1)

        # Dependendo do tipo de view, envia as informações formatadas
        if isinstance(view.strategy, View_Tabela):
            view.display(self.tabela)
        elif isinstance(view.strategy, View_Tweets):
            # Prepara os dados para o formato de tweet
            tweet_data = [data_team_1.team_data["team_name"], team_goals_1, 
                          data_team_2.team_data["team_name"], team_goals_2]
            view.display(tweet_data)


    def find(self, team_name):
        if team_name not in self.tabela:
            self.tabela[team_name] = Team(team_name)

        return self.tabela[team_name]

    def set(self, team_name, data):
        self.tabela[team_name] = data
    