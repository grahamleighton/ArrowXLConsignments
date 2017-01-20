object frmOption: TfrmOption
  Left = 0
  Top = 0
  Width = 577
  Height = 402
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 577
    Height = 41
    Align = alTop
    Caption = 'Choose Option'
    TabOrder = 0
    ExplicitLeft = 64
    ExplicitTop = 48
    ExplicitWidth = 185
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 577
    Height = 303
    Align = alClient
    TabOrder = 1
    ExplicitLeft = 160
    ExplicitTop = 264
    ExplicitWidth = 185
    ExplicitHeight = 41
    object DBGrid1: TDBGrid
      Left = 1
      Top = 1
      Width = 575
      Height = 301
      Align = alClient
      DataSource = DM.dsItemLookup
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 344
    Width = 577
    Height = 58
    Align = alBottom
    TabOrder = 2
  end
end
