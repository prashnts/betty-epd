import pandas as pd

from . import consts


def load_logic_analysis(fname: str) -> pd.DataFrame:
  '''Load Logic Analyser data as pandas dataframe.'''
  df = pd.read_csv(fname, header=0, names=['t', 'data'], usecols=[0, 2])
  df['data'] = df.data.str.replace('MOSI: ', '')

  return df


def decode_dataframe(encoded: pd.DataFrame) -> pd.DataFrame:
  '''Parse logic data and decode values with commands.'''
  df = encoded.copy()

  df['flag'] = df.data.str.startswith('0x1')

  df['cmd'] = df.data.apply(lambda x: consts.cmds.get(x, ''))

  return df
