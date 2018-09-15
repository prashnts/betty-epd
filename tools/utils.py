import pandas as pd


def load_logic_analysis(fname: str) -> pd.DataFrame:
  '''Load Logic Analyser data as pandas dataframe.'''
  df = pd.read_csv(fname, header=0, names=['t', 'data'], usecols=[0, 2])
  df['data'] = df.data.str.replace('MOSI: ', '')

  df['flag'] = df.data.str.startswith('0x1')

  return df
