object fmOptSelect: TfmOptSelect
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'fmOptSelect'
  ClientHeight = 346
  ClientWidth = 537
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 18
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 537
    Height = 41
    Align = alTop
    Caption = 'Choose Option'
    TabOrder = 0
    ExplicitLeft = 120
    ExplicitTop = 48
    ExplicitWidth = 185
  end
  object Panel2: TPanel
    Left = 0
    Top = 305
    Width = 537
    Height = 41
    Align = alBottom
    TabOrder = 1
    ExplicitLeft = 176
    ExplicitTop = 216
    ExplicitWidth = 185
    object Button1: TButton
      Left = 56
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Select'
      Default = True
      ModalResult = 1
      TabOrder = 0
    end
    object Button2: TButton
      Left = 408
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 41
    Width = 537
    Height = 264
    Align = alClient
    Caption = 'Panel3'
    TabOrder = 2
    ExplicitLeft = 192
    ExplicitTop = 192
    ExplicitWidth = 185
    ExplicitHeight = 41
    object DBGrid1: TDBGrid
      Left = 1
      Top = 1
      Width = 535
      Height = 262
      Align = alClient
      Color = clMoneyGreen
      DataSource = DM.dsItemLookup
      Options = [dgTitles, dgColumnResize, dgColLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -15
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'Cat'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Opt'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Description'
          Width = 300
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Dim1'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'Dim2'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'Dim3'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'Volume'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'Weight'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'Price'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'OptionID'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'HDNLCode'
          Visible = True
        end>
    end
  end
end
