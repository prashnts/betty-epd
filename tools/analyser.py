import pandas as pd

from . import consts


class LogicData:
  '''Load, parse, and resolve logic data'''
  def __init__(self, df: pd.DataFrame):
    # initialising class expects a dataframe with columns `t` and `data`.
    # The decoded values may be prefixed with `MOSI:`.

    self._df = df
    self.df = self._decode(df)

  def _decode(self, encoded: pd.DataFrame) -> pd.DataFrame:
    '''Parse logic data and decode values with commands.'''
    df = encoded.copy()

    # Clean the prefixes.
    df['data'] = df.data.str.replace('MOSI: ', '')

    # Parse command bits and resolve them to defined values
    df['flag'] = df.data.str.startswith('0x1')
    df['cmd'] = df.data.apply(lambda x: consts.cmds.get(x, ''))

    # Parse the data/command directive bits.
    df['v_data'] = df.data.str.replace('0x1', '').apply(lambda x: int(x, 16))

    return df

  @classmethod
  def from_csv(cls, fname: str) -> 'LogicData':
    '''Load Logic Analyser data as pandas dataframe.'''
    df = pd.read_csv(fname, header=0, names=['t', 'data'], usecols=[0, 2])
    return LogicData(df)

