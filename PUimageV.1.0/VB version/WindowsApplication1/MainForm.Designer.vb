<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class MainForm
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainForm))
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.FileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.EditorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ViewToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AnalysisToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.EmbossToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AverageFilterToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SimpleSmoothingToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.HelpToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.SaveImage = New System.Windows.Forms.SaveFileDialog()
        Me.ContextMenuStrip1 = New System.Windows.Forms.ContextMenuStrip(Me.components)
        Me.ColorDialog1 = New System.Windows.Forms.ColorDialog()
        Me.Panel1 = New System.Windows.Forms.Panel()
        Me.Panel2 = New System.Windows.Forms.Panel()
        Me.Panel3 = New System.Windows.Forms.Panel()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.ProgressBar1 = New System.Windows.Forms.ProgressBar()
        Me.ToolStrip1 = New System.Windows.Forms.ToolStrip()
        Me.ToolStripButton1 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripButton2 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripButton3 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripButton4 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripButton5 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripButton6 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripDropDownButton1 = New System.Windows.Forms.ToolStripDropDownButton()
        Me.FitScreenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.FitWidthToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.FitHeightToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem2 = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem3 = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem4 = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem5 = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem6 = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem7 = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripButton7 = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripButton8 = New System.Windows.Forms.ToolStripButton()
        Me.PicImage = New System.Windows.Forms.PictureBox()
        Me.OpenAnImageToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SaveToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ExitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.UndoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RedoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CopyToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PasteToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ResetToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomToFitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomToInToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomToOutToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.FitToScreenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RightRotateToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LeftRotateToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AutoEnhanceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ColorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ContrastToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BrightenssToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ColorContrastToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.HistogramBalanceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ColorBalanceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.InvertToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.InvertToRGBToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.InvertToToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ImageEnhancementToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GrayShadeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PUIPHelpToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AboutPUIPToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MenuStrip1.SuspendLayout()
        Me.ToolStrip1.SuspendLayout()
        CType(Me.PicImage, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem, Me.EditorToolStripMenuItem, Me.ViewToolStripMenuItem, Me.AnalysisToolStripMenuItem, Me.HelpToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Padding = New System.Windows.Forms.Padding(8, 2, 0, 2)
        Me.MenuStrip1.Size = New System.Drawing.Size(1182, 24)
        Me.MenuStrip1.TabIndex = 0
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.OpenAnImageToolStripMenuItem, Me.SaveToolStripMenuItem, Me.ExitToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(37, 20)
        Me.FileToolStripMenuItem.Text = "File"
        '
        'EditorToolStripMenuItem
        '
        Me.EditorToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.UndoToolStripMenuItem, Me.RedoToolStripMenuItem, Me.CopyToolStripMenuItem, Me.PasteToolStripMenuItem, Me.ResetToolStripMenuItem})
        Me.EditorToolStripMenuItem.Name = "EditorToolStripMenuItem"
        Me.EditorToolStripMenuItem.Size = New System.Drawing.Size(50, 20)
        Me.EditorToolStripMenuItem.Text = "Editor"
        '
        'ViewToolStripMenuItem
        '
        Me.ViewToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ZoomToFitToolStripMenuItem, Me.ZoomToInToolStripMenuItem, Me.ZoomToOutToolStripMenuItem, Me.FitToScreenToolStripMenuItem, Me.RightRotateToolStripMenuItem, Me.LeftRotateToolStripMenuItem})
        Me.ViewToolStripMenuItem.Name = "ViewToolStripMenuItem"
        Me.ViewToolStripMenuItem.Size = New System.Drawing.Size(44, 20)
        Me.ViewToolStripMenuItem.Text = "View"
        '
        'AnalysisToolStripMenuItem
        '
        Me.AnalysisToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.AutoEnhanceToolStripMenuItem, Me.BrightenssToolStripMenuItem, Me.ColorContrastToolStripMenuItem, Me.EmbossToolStripMenuItem, Me.HistogramBalanceToolStripMenuItem, Me.ColorBalanceToolStripMenuItem, Me.InvertToolStripMenuItem, Me.ImageEnhancementToolStripMenuItem, Me.AverageFilterToolStripMenuItem, Me.SimpleSmoothingToolStripMenuItem, Me.GrayShadeToolStripMenuItem})
        Me.AnalysisToolStripMenuItem.Name = "AnalysisToolStripMenuItem"
        Me.AnalysisToolStripMenuItem.Size = New System.Drawing.Size(86, 20)
        Me.AnalysisToolStripMenuItem.Text = "Adjustments"
        '
        'EmbossToolStripMenuItem
        '
        Me.EmbossToolStripMenuItem.Name = "EmbossToolStripMenuItem"
        Me.EmbossToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.EmbossToolStripMenuItem.Text = "Emboss"
        '
        'AverageFilterToolStripMenuItem
        '
        Me.AverageFilterToolStripMenuItem.Name = "AverageFilterToolStripMenuItem"
        Me.AverageFilterToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.AverageFilterToolStripMenuItem.Text = "Average Filter"
        '
        'SimpleSmoothingToolStripMenuItem
        '
        Me.SimpleSmoothingToolStripMenuItem.Name = "SimpleSmoothingToolStripMenuItem"
        Me.SimpleSmoothingToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.SimpleSmoothingToolStripMenuItem.Text = "Simple Smoothing"
        '
        'HelpToolStripMenuItem
        '
        Me.HelpToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.PUIPHelpToolStripMenuItem, Me.AboutPUIPToolStripMenuItem})
        Me.HelpToolStripMenuItem.Name = "HelpToolStripMenuItem"
        Me.HelpToolStripMenuItem.Size = New System.Drawing.Size(44, 20)
        Me.HelpToolStripMenuItem.Text = "Help"
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'ContextMenuStrip1
        '
        Me.ContextMenuStrip1.Name = "ContextMenuStrip1"
        Me.ContextMenuStrip1.Size = New System.Drawing.Size(61, 4)
        '
        'Panel1
        '
        Me.Panel1.BackColor = System.Drawing.Color.FromArgb(CType(CType(255, Byte), Integer), CType(CType(224, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.Panel1.Location = New System.Drawing.Point(857, 78)
        Me.Panel1.Margin = New System.Windows.Forms.Padding(4)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(298, 168)
        Me.Panel1.TabIndex = 5
        '
        'Panel2
        '
        Me.Panel2.BackColor = System.Drawing.Color.FromArgb(CType(CType(255, Byte), Integer), CType(CType(224, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.Panel2.Location = New System.Drawing.Point(857, 254)
        Me.Panel2.Margin = New System.Windows.Forms.Padding(4)
        Me.Panel2.Name = "Panel2"
        Me.Panel2.Size = New System.Drawing.Size(298, 172)
        Me.Panel2.TabIndex = 6
        '
        'Panel3
        '
        Me.Panel3.BackColor = System.Drawing.Color.FromArgb(CType(CType(255, Byte), Integer), CType(CType(224, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.Panel3.Location = New System.Drawing.Point(857, 434)
        Me.Panel3.Margin = New System.Windows.Forms.Padding(4)
        Me.Panel3.Name = "Panel3"
        Me.Panel3.Size = New System.Drawing.Size(298, 178)
        Me.Panel3.TabIndex = 7
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(857, 58)
        Me.Label1.Margin = New System.Windows.Forms.Padding(4, 0, 4, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(115, 16)
        Me.Label1.TabIndex = 8
        Me.Label1.Text = "Histogram RGB"
        '
        'ProgressBar1
        '
        Me.ProgressBar1.Location = New System.Drawing.Point(16, 620)
        Me.ProgressBar1.Margin = New System.Windows.Forms.Padding(4)
        Me.ProgressBar1.Name = "ProgressBar1"
        Me.ProgressBar1.Size = New System.Drawing.Size(821, 22)
        Me.ProgressBar1.TabIndex = 9
        '
        'ToolStrip1
        '
        Me.ToolStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ToolStripButton1, Me.ToolStripButton2, Me.ToolStripButton3, Me.ToolStripButton4, Me.ToolStripButton5, Me.ToolStripButton6, Me.ToolStripDropDownButton1, Me.ToolStripButton7, Me.ToolStripButton8})
        Me.ToolStrip1.Location = New System.Drawing.Point(0, 24)
        Me.ToolStrip1.Name = "ToolStrip1"
        Me.ToolStrip1.Size = New System.Drawing.Size(1182, 25)
        Me.ToolStrip1.TabIndex = 10
        Me.ToolStrip1.Text = "ToolStrip1"
        '
        'ToolStripButton1
        '
        Me.ToolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton1.Image = CType(resources.GetObject("ToolStripButton1.Image"), System.Drawing.Image)
        Me.ToolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton1.Name = "ToolStripButton1"
        Me.ToolStripButton1.RightToLeftAutoMirrorImage = True
        Me.ToolStripButton1.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton1.Text = "Open an image"
        '
        'ToolStripButton2
        '
        Me.ToolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton2.Image = CType(resources.GetObject("ToolStripButton2.Image"), System.Drawing.Image)
        Me.ToolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton2.Name = "ToolStripButton2"
        Me.ToolStripButton2.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton2.Text = "save"
        '
        'ToolStripButton3
        '
        Me.ToolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton3.Image = CType(resources.GetObject("ToolStripButton3.Image"), System.Drawing.Image)
        Me.ToolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton3.Name = "ToolStripButton3"
        Me.ToolStripButton3.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton3.Text = "redo"
        '
        'ToolStripButton4
        '
        Me.ToolStripButton4.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton4.Image = CType(resources.GetObject("ToolStripButton4.Image"), System.Drawing.Image)
        Me.ToolStripButton4.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton4.Name = "ToolStripButton4"
        Me.ToolStripButton4.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton4.Text = "undo"
        '
        'ToolStripButton5
        '
        Me.ToolStripButton5.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton5.Image = CType(resources.GetObject("ToolStripButton5.Image"), System.Drawing.Image)
        Me.ToolStripButton5.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton5.Name = "ToolStripButton5"
        Me.ToolStripButton5.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton5.Text = "zoom out"
        '
        'ToolStripButton6
        '
        Me.ToolStripButton6.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton6.Image = CType(resources.GetObject("ToolStripButton6.Image"), System.Drawing.Image)
        Me.ToolStripButton6.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton6.Name = "ToolStripButton6"
        Me.ToolStripButton6.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton6.Text = "zoom in"
        '
        'ToolStripDropDownButton1
        '
        Me.ToolStripDropDownButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripDropDownButton1.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FitScreenToolStripMenuItem, Me.FitWidthToolStripMenuItem, Me.FitHeightToolStripMenuItem, Me.ToolStripMenuItem2, Me.ToolStripMenuItem3, Me.ToolStripMenuItem4, Me.ToolStripMenuItem5, Me.ToolStripMenuItem6, Me.ToolStripMenuItem7})
        Me.ToolStripDropDownButton1.Image = CType(resources.GetObject("ToolStripDropDownButton1.Image"), System.Drawing.Image)
        Me.ToolStripDropDownButton1.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripDropDownButton1.Name = "ToolStripDropDownButton1"
        Me.ToolStripDropDownButton1.Size = New System.Drawing.Size(29, 22)
        Me.ToolStripDropDownButton1.Text = "ToolStripDropDownButton1"
        '
        'FitScreenToolStripMenuItem
        '
        Me.FitScreenToolStripMenuItem.Name = "FitScreenToolStripMenuItem"
        Me.FitScreenToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.FitScreenToolStripMenuItem.Text = "Fit Screen"
        '
        'FitWidthToolStripMenuItem
        '
        Me.FitWidthToolStripMenuItem.Name = "FitWidthToolStripMenuItem"
        Me.FitWidthToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.FitWidthToolStripMenuItem.Text = "Fit Width"
        '
        'FitHeightToolStripMenuItem
        '
        Me.FitHeightToolStripMenuItem.Name = "FitHeightToolStripMenuItem"
        Me.FitHeightToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.FitHeightToolStripMenuItem.Text = "Fit Height"
        '
        'ToolStripMenuItem2
        '
        Me.ToolStripMenuItem2.Name = "ToolStripMenuItem2"
        Me.ToolStripMenuItem2.Size = New System.Drawing.Size(152, 22)
        Me.ToolStripMenuItem2.Text = "100%"
        '
        'ToolStripMenuItem3
        '
        Me.ToolStripMenuItem3.Name = "ToolStripMenuItem3"
        Me.ToolStripMenuItem3.Size = New System.Drawing.Size(152, 22)
        Me.ToolStripMenuItem3.Text = "80%"
        '
        'ToolStripMenuItem4
        '
        Me.ToolStripMenuItem4.Name = "ToolStripMenuItem4"
        Me.ToolStripMenuItem4.Size = New System.Drawing.Size(152, 22)
        Me.ToolStripMenuItem4.Text = "60%"
        '
        'ToolStripMenuItem5
        '
        Me.ToolStripMenuItem5.Name = "ToolStripMenuItem5"
        Me.ToolStripMenuItem5.Size = New System.Drawing.Size(152, 22)
        Me.ToolStripMenuItem5.Text = "40%"
        '
        'ToolStripMenuItem6
        '
        Me.ToolStripMenuItem6.Name = "ToolStripMenuItem6"
        Me.ToolStripMenuItem6.Size = New System.Drawing.Size(152, 22)
        Me.ToolStripMenuItem6.Text = "20%"
        '
        'ToolStripMenuItem7
        '
        Me.ToolStripMenuItem7.Name = "ToolStripMenuItem7"
        Me.ToolStripMenuItem7.Size = New System.Drawing.Size(152, 22)
        Me.ToolStripMenuItem7.Text = "10%"
        '
        'ToolStripButton7
        '
        Me.ToolStripButton7.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton7.Image = CType(resources.GetObject("ToolStripButton7.Image"), System.Drawing.Image)
        Me.ToolStripButton7.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton7.Name = "ToolStripButton7"
        Me.ToolStripButton7.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton7.Text = "reset"
        '
        'ToolStripButton8
        '
        Me.ToolStripButton8.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton8.Image = Global.WindowsApplication1.My.Resources.Resources.help
        Me.ToolStripButton8.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton8.Name = "ToolStripButton8"
        Me.ToolStripButton8.Size = New System.Drawing.Size(23, 22)
        Me.ToolStripButton8.Text = "help"
        '
        'PicImage
        '
        Me.PicImage.BackColor = System.Drawing.SystemColors.ActiveBorder
        Me.PicImage.Location = New System.Drawing.Point(16, 60)
        Me.PicImage.Margin = New System.Windows.Forms.Padding(4)
        Me.PicImage.Name = "PicImage"
        Me.PicImage.Size = New System.Drawing.Size(821, 552)
        Me.PicImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.PicImage.TabIndex = 1
        Me.PicImage.TabStop = False
        '
        'OpenAnImageToolStripMenuItem
        '
        Me.OpenAnImageToolStripMenuItem.Image = CType(resources.GetObject("OpenAnImageToolStripMenuItem.Image"), System.Drawing.Image)
        Me.OpenAnImageToolStripMenuItem.Name = "OpenAnImageToolStripMenuItem"
        Me.OpenAnImageToolStripMenuItem.Size = New System.Drawing.Size(155, 22)
        Me.OpenAnImageToolStripMenuItem.Text = "Open an image"
        '
        'SaveToolStripMenuItem
        '
        Me.SaveToolStripMenuItem.Image = CType(resources.GetObject("SaveToolStripMenuItem.Image"), System.Drawing.Image)
        Me.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem"
        Me.SaveToolStripMenuItem.Size = New System.Drawing.Size(155, 22)
        Me.SaveToolStripMenuItem.Text = "Save"
        '
        'ExitToolStripMenuItem
        '
        Me.ExitToolStripMenuItem.Image = CType(resources.GetObject("ExitToolStripMenuItem.Image"), System.Drawing.Image)
        Me.ExitToolStripMenuItem.Name = "ExitToolStripMenuItem"
        Me.ExitToolStripMenuItem.Size = New System.Drawing.Size(155, 22)
        Me.ExitToolStripMenuItem.Text = "Exit"
        '
        'UndoToolStripMenuItem
        '
        Me.UndoToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.undo
        Me.UndoToolStripMenuItem.Name = "UndoToolStripMenuItem"
        Me.UndoToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.UndoToolStripMenuItem.Text = "Undo"
        '
        'RedoToolStripMenuItem
        '
        Me.RedoToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.redo
        Me.RedoToolStripMenuItem.Name = "RedoToolStripMenuItem"
        Me.RedoToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.RedoToolStripMenuItem.Text = "Redo"
        '
        'CopyToolStripMenuItem
        '
        Me.CopyToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.copy
        Me.CopyToolStripMenuItem.Name = "CopyToolStripMenuItem"
        Me.CopyToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.CopyToolStripMenuItem.Text = "Copy"
        '
        'PasteToolStripMenuItem
        '
        Me.PasteToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.paste
        Me.PasteToolStripMenuItem.Name = "PasteToolStripMenuItem"
        Me.PasteToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.PasteToolStripMenuItem.Text = "Paste"
        '
        'ResetToolStripMenuItem
        '
        Me.ResetToolStripMenuItem.Image = CType(resources.GetObject("ResetToolStripMenuItem.Image"), System.Drawing.Image)
        Me.ResetToolStripMenuItem.Name = "ResetToolStripMenuItem"
        Me.ResetToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.ResetToolStripMenuItem.Text = "Reset"
        '
        'ZoomToFitToolStripMenuItem
        '
        Me.ZoomToFitToolStripMenuItem.Image = CType(resources.GetObject("ZoomToFitToolStripMenuItem.Image"), System.Drawing.Image)
        Me.ZoomToFitToolStripMenuItem.Name = "ZoomToFitToolStripMenuItem"
        Me.ZoomToFitToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ZoomToFitToolStripMenuItem.Text = "Initial Size"
        '
        'ZoomToInToolStripMenuItem
        '
        Me.ZoomToInToolStripMenuItem.Image = CType(resources.GetObject("ZoomToInToolStripMenuItem.Image"), System.Drawing.Image)
        Me.ZoomToInToolStripMenuItem.Name = "ZoomToInToolStripMenuItem"
        Me.ZoomToInToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ZoomToInToolStripMenuItem.Text = "Zoom In"
        '
        'ZoomToOutToolStripMenuItem
        '
        Me.ZoomToOutToolStripMenuItem.Image = CType(resources.GetObject("ZoomToOutToolStripMenuItem.Image"), System.Drawing.Image)
        Me.ZoomToOutToolStripMenuItem.Name = "ZoomToOutToolStripMenuItem"
        Me.ZoomToOutToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ZoomToOutToolStripMenuItem.Text = "Zoom Out"
        '
        'FitToScreenToolStripMenuItem
        '
        Me.FitToScreenToolStripMenuItem.Image = CType(resources.GetObject("FitToScreenToolStripMenuItem.Image"), System.Drawing.Image)
        Me.FitToScreenToolStripMenuItem.Name = "FitToScreenToolStripMenuItem"
        Me.FitToScreenToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.FitToScreenToolStripMenuItem.Text = "Fit to Screen"
        '
        'RightRotateToolStripMenuItem
        '
        Me.RightRotateToolStripMenuItem.Image = CType(resources.GetObject("RightRotateToolStripMenuItem.Image"), System.Drawing.Image)
        Me.RightRotateToolStripMenuItem.Name = "RightRotateToolStripMenuItem"
        Me.RightRotateToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.RightRotateToolStripMenuItem.Text = "Right Rotate"
        '
        'LeftRotateToolStripMenuItem
        '
        Me.LeftRotateToolStripMenuItem.Image = CType(resources.GetObject("LeftRotateToolStripMenuItem.Image"), System.Drawing.Image)
        Me.LeftRotateToolStripMenuItem.Name = "LeftRotateToolStripMenuItem"
        Me.LeftRotateToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.LeftRotateToolStripMenuItem.Text = "Left Rotate"
        '
        'AutoEnhanceToolStripMenuItem
        '
        Me.AutoEnhanceToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ColorToolStripMenuItem, Me.ContrastToolStripMenuItem})
        Me.AutoEnhanceToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.autoenhance
        Me.AutoEnhanceToolStripMenuItem.Name = "AutoEnhanceToolStripMenuItem"
        Me.AutoEnhanceToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.AutoEnhanceToolStripMenuItem.Text = "Auto Enhance"
        '
        'ColorToolStripMenuItem
        '
        Me.ColorToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.brightness
        Me.ColorToolStripMenuItem.Name = "ColorToolStripMenuItem"
        Me.ColorToolStripMenuItem.Size = New System.Drawing.Size(129, 22)
        Me.ColorToolStripMenuItem.Text = "Brightness"
        '
        'ContrastToolStripMenuItem
        '
        Me.ContrastToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.contrast
        Me.ContrastToolStripMenuItem.Name = "ContrastToolStripMenuItem"
        Me.ContrastToolStripMenuItem.Size = New System.Drawing.Size(129, 22)
        Me.ContrastToolStripMenuItem.Text = "Contrast"
        '
        'BrightenssToolStripMenuItem
        '
        Me.BrightenssToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.brightness
        Me.BrightenssToolStripMenuItem.Name = "BrightenssToolStripMenuItem"
        Me.BrightenssToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.BrightenssToolStripMenuItem.Text = "Brightenss"
        '
        'ColorContrastToolStripMenuItem
        '
        Me.ColorContrastToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.contrast
        Me.ColorContrastToolStripMenuItem.Name = "ColorContrastToolStripMenuItem"
        Me.ColorContrastToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.ColorContrastToolStripMenuItem.Text = "Contrast"
        '
        'HistogramBalanceToolStripMenuItem
        '
        Me.HistogramBalanceToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.histogram
        Me.HistogramBalanceToolStripMenuItem.Name = "HistogramBalanceToolStripMenuItem"
        Me.HistogramBalanceToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.HistogramBalanceToolStripMenuItem.Text = "Histogram equalization"
        '
        'ColorBalanceToolStripMenuItem
        '
        Me.ColorBalanceToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.colorbalance
        Me.ColorBalanceToolStripMenuItem.Name = "ColorBalanceToolStripMenuItem"
        Me.ColorBalanceToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.ColorBalanceToolStripMenuItem.Text = "Color Balance"
        '
        'InvertToolStripMenuItem
        '
        Me.InvertToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.InvertToRGBToolStripMenuItem, Me.InvertToToolStripMenuItem})
        Me.InvertToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.invert
        Me.InvertToolStripMenuItem.Name = "InvertToolStripMenuItem"
        Me.InvertToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.InvertToolStripMenuItem.Text = "Invert"
        '
        'InvertToRGBToolStripMenuItem
        '
        Me.InvertToRGBToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.RGB
        Me.InvertToRGBToolStripMenuItem.Name = "InvertToRGBToolStripMenuItem"
        Me.InvertToRGBToolStripMenuItem.Size = New System.Drawing.Size(212, 22)
        Me.InvertToRGBToolStripMenuItem.Text = "Invert to RGB"
        '
        'InvertToToolStripMenuItem
        '
        Me.InvertToToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.negative
        Me.InvertToToolStripMenuItem.Name = "InvertToToolStripMenuItem"
        Me.InvertToToolStripMenuItem.Size = New System.Drawing.Size(212, 22)
        Me.InvertToToolStripMenuItem.Text = "Invert to CMYK (Negative)"
        '
        'ImageEnhancementToolStripMenuItem
        '
        Me.ImageEnhancementToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.enhance
        Me.ImageEnhancementToolStripMenuItem.Name = "ImageEnhancementToolStripMenuItem"
        Me.ImageEnhancementToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.ImageEnhancementToolStripMenuItem.Text = "Color Enhancement"
        '
        'GrayShadeToolStripMenuItem
        '
        Me.GrayShadeToolStripMenuItem.Image = Global.WindowsApplication1.My.Resources.Resources.gray
        Me.GrayShadeToolStripMenuItem.Name = "GrayShadeToolStripMenuItem"
        Me.GrayShadeToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.GrayShadeToolStripMenuItem.Text = "Gray Shade"
        '
        'PUIPHelpToolStripMenuItem
        '
        Me.PUIPHelpToolStripMenuItem.Image = CType(resources.GetObject("PUIPHelpToolStripMenuItem.Image"), System.Drawing.Image)
        Me.PUIPHelpToolStripMenuItem.Name = "PUIPHelpToolStripMenuItem"
        Me.PUIPHelpToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.PUIPHelpToolStripMenuItem.Text = "PUIP help"
        '
        'AboutPUIPToolStripMenuItem
        '
        Me.AboutPUIPToolStripMenuItem.Image = CType(resources.GetObject("AboutPUIPToolStripMenuItem.Image"), System.Drawing.Image)
        Me.AboutPUIPToolStripMenuItem.Name = "AboutPUIPToolStripMenuItem"
        Me.AboutPUIPToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.AboutPUIPToolStripMenuItem.Text = "About PUIP"
        '
        'MainForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1182, 657)
        Me.Controls.Add(Me.ToolStrip1)
        Me.Controls.Add(Me.ProgressBar1)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Panel3)
        Me.Controls.Add(Me.Panel2)
        Me.Controls.Add(Me.Panel1)
        Me.Controls.Add(Me.PicImage)
        Me.Controls.Add(Me.MenuStrip1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.Name = "MainForm"
        Me.Text = " PUimage"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.ToolStrip1.ResumeLayout(False)
        Me.ToolStrip1.PerformLayout()
        CType(Me.PicImage, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents FileToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents EditorToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ViewToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents AnalysisToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents HelpToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents OpenAnImageToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SaveToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ExitToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents UndoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RedoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents PicImage As System.Windows.Forms.PictureBox
    Friend WithEvents SaveImage As System.Windows.Forms.SaveFileDialog
    Friend WithEvents ZoomToFitToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ZoomToInToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ZoomToOutToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents PUIPHelpToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents AboutPUIPToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ContextMenuStrip1 As System.Windows.Forms.ContextMenuStrip
    Friend WithEvents RightRotateToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents LeftRotateToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ColorDialog1 As ColorDialog
    Friend WithEvents Panel1 As Panel
    Friend WithEvents Panel2 As Panel
    Friend WithEvents Panel3 As Panel
    Friend WithEvents Label1 As Label
    Friend WithEvents BrightenssToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ProgressBar1 As ProgressBar
    Friend WithEvents GrayShadeToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents HistogramBalanceToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AverageFilterToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ColorContrastToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SimpleSmoothingToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents EmbossToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStrip1 As ToolStrip
    Friend WithEvents ToolStripButton1 As ToolStripButton
    Friend WithEvents ToolStripButton2 As ToolStripButton
    Friend WithEvents ToolStripButton3 As ToolStripButton
    Friend WithEvents ToolStripButton4 As ToolStripButton
    Friend WithEvents ToolStripButton5 As ToolStripButton
    Friend WithEvents ToolStripButton6 As ToolStripButton
    Friend WithEvents CopyToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents PasteToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripButton7 As ToolStripButton
    Friend WithEvents FitToScreenToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripDropDownButton1 As ToolStripDropDownButton
    Friend WithEvents ToolStripMenuItem2 As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem3 As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem4 As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem5 As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem6 As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem7 As ToolStripMenuItem
    Friend WithEvents FitScreenToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents FitWidthToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents FitHeightToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AutoEnhanceToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ResetToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ColorToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ContrastToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ImageEnhancementToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents InvertToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents InvertToRGBToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents InvertToToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ColorBalanceToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripButton8 As ToolStripButton
End Class
