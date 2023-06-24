player_df = df_per_90.loc[df_per_90["shortName"] == "Mohamed player_df"]
#columns similar together
player_df = player_df[['npxG_per90', "goals_per90", "assists_per90", "key_passes_per90", "smart_passes_per90", "final_third_passes_per90", "final_third_receptions_per90", "ground_duels_won_per90", "air_duels_won_per90"]]
#take only necessary columns - exclude playerId
per_90_columns = player_df.columns[:]
#values to mark on the plot
values = [round(player_df[column].iloc[0],2) for column in per_90_columns]
#percentiles
percentiles = [int(stats.percentileofscore(df_per_90[column], player_df[column].iloc[0])) for column in per_90_columns]