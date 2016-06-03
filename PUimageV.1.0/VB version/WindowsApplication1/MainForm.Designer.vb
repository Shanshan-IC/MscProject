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
        Me.OpenAnImageToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SaveToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ExitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.EditorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.UndoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RedoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CopyToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PasteToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ViewToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomToFitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomToInToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ZoomToOutToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RightRotateToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LeftRotateToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AnalysisToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NeighborhoodFilterToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MeanFilterToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MedianFilterToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.VerticleToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NegationToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GrayShadeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BrightenssToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.HistogramBalanceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AutoContrastToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AverageFilterToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ColorContrastToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SimpleSmoothingToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NeonToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.HelpToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PUIPHelpToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AboutPUIPToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.PicImage = New System.Windows.Forms.PictureBox()
        Me.SaveImage = New System.Windows.Forms.SaveFileDialog()
        Me.ContextMenuStrip1 = New System.Windows.Forms.ContextMenuStrip(Me.components)
        Me.Button1 = New System.Windows.Forms.Button()
        Me.ToolStrip1 = New System.Windows.Forms.ToolStrip()
        Me.Zoom1Tool = New System.Windows.Forms.ToolStripButton()
        Me.Zoom = New System.Windows.Forms.ToolStripComboBox()
        Me.ColorDialog1 = New System.Windows.Forms.ColorDialog()
        Me.Panel1 = New System.Windows.Forms.Panel()
        Me.Panel2 = New System.Windows.Forms.Panel()
        Me.Panel3 = New System.Windows.Forms.Panel()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.ProgressBar1 = New System.Windows.Forms.ProgressBar()
        Me.SharpenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MenuStrip1.SuspendLayout()
        CType(Me.PicImage, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.ToolStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem, Me.EditorToolStripMenuItem, Me.ViewToolStripMenuItem, Me.AnalysisToolStripMenuItem, Me.HelpToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(981, 24)
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
        'OpenAnImageToolStripMenuItem
        '
        Me.OpenAnImageToolStripMenuItem.Name = "OpenAnImageToolStripMenuItem"
        Me.OpenAnImageToolStripMenuItem.Size = New System.Drawing.Size(155, 22)
        Me.OpenAnImageToolStripMenuItem.Text = "Open an image"
        '
        'SaveToolStripMenuItem
        '
        Me.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem"
        Me.SaveToolStripMenuItem.Size = New System.Drawing.Size(155, 22)
        Me.SaveToolStripMenuItem.Text = "Save"
        '
        'ExitToolStripMenuItem
        '
        Me.ExitToolStripMenuItem.Name = "ExitToolStripMenuItem"
        Me.ExitToolStripMenuItem.Size = New System.Drawing.Size(155, 22)
        Me.ExitToolStripMenuItem.Text = "Exit"
        '
        'EditorToolStripMenuItem
        '
        Me.EditorToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.UndoToolStripMenuItem, Me.RedoToolStripMenuItem, Me.CopyToolStripMenuItem, Me.PasteToolStripMenuItem})
        Me.EditorToolStripMenuItem.Name = "EditorToolStripMenuItem"
        Me.EditorToolStripMenuItem.Size = New System.Drawing.Size(50, 20)
        Me.EditorToolStripMenuItem.Text = "Editor"
        '
        'UndoToolStripMenuItem
        '
        Me.UndoToolStripMenuItem.Name = "UndoToolStripMenuItem"
        Me.UndoToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.UndoToolStripMenuItem.Text = "Undo"
        '
        'RedoToolStripMenuItem
        '
        Me.RedoToolStripMenuItem.Name = "RedoToolStripMenuItem"
        Me.RedoToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.RedoToolStripMenuItem.Text = "Redo"
        '
        'CopyToolStripMenuItem
        '
        Me.CopyToolStripMenuItem.Name = "CopyToolStripMenuItem"
        Me.CopyToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.CopyToolStripMenuItem.Text = "Copy"
        '
        'PasteToolStripMenuItem
        '
        Me.PasteToolStripMenuItem.Name = "PasteToolStripMenuItem"
        Me.PasteToolStripMenuItem.Size = New System.Drawing.Size(103, 22)
        Me.PasteToolStripMenuItem.Text = "Paste"
        '
        'ViewToolStripMenuItem
        '
        Me.ViewToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ZoomToFitToolStripMenuItem, Me.ZoomToInToolStripMenuItem, Me.ZoomToOutToolStripMenuItem, Me.RightRotateToolStripMenuItem, Me.LeftRotateToolStripMenuItem})
        Me.ViewToolStripMenuItem.Name = "ViewToolStripMenuItem"
        Me.ViewToolStripMenuItem.Size = New System.Drawing.Size(44, 20)
        Me.ViewToolStripMenuItem.Text = "View"
        '
        'ZoomToFitToolStripMenuItem
        '
        Me.ZoomToFitToolStripMenuItem.Name = "ZoomToFitToolStripMenuItem"
        Me.ZoomToFitToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.ZoomToFitToolStripMenuItem.Text = "Initial Size"
        '
        'ZoomToInToolStripMenuItem
        '
        Me.ZoomToInToolStripMenuItem.Name = "ZoomToInToolStripMenuItem"
        Me.ZoomToInToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.ZoomToInToolStripMenuItem.Text = "Zoom to In"
        '
        'ZoomToOutToolStripMenuItem
        '
        Me.ZoomToOutToolStripMenuItem.Name = "ZoomToOutToolStripMenuItem"
        Me.ZoomToOutToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.ZoomToOutToolStripMenuItem.Text = "Zoom to Out"
        '
        'RightRotateToolStripMenuItem
        '
        Me.RightRotateToolStripMenuItem.Name = "RightRotateToolStripMenuItem"
        Me.RightRotateToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.RightRotateToolStripMenuItem.Text = "Right Rotate"
        '
        'LeftRotateToolStripMenuItem
        '
        Me.LeftRotateToolStripMenuItem.Name = "LeftRotateToolStripMenuItem"
        Me.LeftRotateToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.LeftRotateToolStripMenuItem.Text = "Left Rotate"
        '
        'AnalysisToolStripMenuItem
        '
        Me.AnalysisToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.NeighborhoodFilterToolStripMenuItem, Me.VerticleToolStripMenuItem, Me.NegationToolStripMenuItem, Me.GrayShadeToolStripMenuItem, Me.BrightenssToolStripMenuItem, Me.HistogramBalanceToolStripMenuItem, Me.AutoContrastToolStripMenuItem, Me.AverageFilterToolStripMenuItem, Me.ColorContrastToolStripMenuItem, Me.SimpleSmoothingToolStripMenuItem, Me.NeonToolStripMenuItem, Me.SharpenToolStripMenuItem})
        Me.AnalysisToolStripMenuItem.Name = "AnalysisToolStripMenuItem"
        Me.AnalysisToolStripMenuItem.Size = New System.Drawing.Size(62, 20)
        Me.AnalysisToolStripMenuItem.Text = "Analysis"
        '
        'NeighborhoodFilterToolStripMenuItem
        '
        Me.NeighborhoodFilterToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.MeanFilterToolStripMenuItem, Me.MedianFilterToolStripMenuItem})
        Me.NeighborhoodFilterToolStripMenuItem.Name = "NeighborhoodFilterToolStripMenuItem"
        Me.NeighborhoodFilterToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.NeighborhoodFilterToolStripMenuItem.Text = "Neighborhood Filter"
        '
        'MeanFilterToolStripMenuItem
        '
        Me.MeanFilterToolStripMenuItem.Name = "MeanFilterToolStripMenuItem"
        Me.MeanFilterToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.MeanFilterToolStripMenuItem.Text = "Mean Filter"
        '
        'MedianFilterToolStripMenuItem
        '
        Me.MedianFilterToolStripMenuItem.Name = "MedianFilterToolStripMenuItem"
        Me.MedianFilterToolStripMenuItem.Size = New System.Drawing.Size(143, 22)
        Me.MedianFilterToolStripMenuItem.Text = "Median Filter"
        '
        'VerticleToolStripMenuItem
        '
        Me.VerticleToolStripMenuItem.Name = "VerticleToolStripMenuItem"
        Me.VerticleToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.VerticleToolStripMenuItem.Text = "Verticle Enhance"
        '
        'NegationToolStripMenuItem
        '
        Me.NegationToolStripMenuItem.Name = "NegationToolStripMenuItem"
        Me.NegationToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.NegationToolStripMenuItem.Text = "Image Inverse"
        '
        'GrayShadeToolStripMenuItem
        '
        Me.GrayShadeToolStripMenuItem.Name = "GrayShadeToolStripMenuItem"
        Me.GrayShadeToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.GrayShadeToolStripMenuItem.Text = "Gray Shade"
        '
        'BrightenssToolStripMenuItem
        '
        Me.BrightenssToolStripMenuItem.Name = "BrightenssToolStripMenuItem"
        Me.BrightenssToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.BrightenssToolStripMenuItem.Text = "Brightenss"
        '
        'HistogramBalanceToolStripMenuItem
        '
        Me.HistogramBalanceToolStripMenuItem.Name = "HistogramBalanceToolStripMenuItem"
        Me.HistogramBalanceToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.HistogramBalanceToolStripMenuItem.Text = "Histogram equalization"
        '
        'AutoContrastToolStripMenuItem
        '
        Me.AutoContrastToolStripMenuItem.Name = "AutoContrastToolStripMenuItem"
        Me.AutoContrastToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.AutoContrastToolStripMenuItem.Text = "Auto Contrast"
        '
        'AverageFilterToolStripMenuItem
        '
        Me.AverageFilterToolStripMenuItem.Name = "AverageFilterToolStripMenuItem"
        Me.AverageFilterToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.AverageFilterToolStripMenuItem.Text = "Average Filter"
        '
        'ColorContrastToolStripMenuItem
        '
        Me.ColorContrastToolStripMenuItem.Name = "ColorContrastToolStripMenuItem"
        Me.ColorContrastToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.ColorContrastToolStripMenuItem.Text = "Color Contrast"
        '
        'SimpleSmoothingToolStripMenuItem
        '
        Me.SimpleSmoothingToolStripMenuItem.Name = "SimpleSmoothingToolStripMenuItem"
        Me.SimpleSmoothingToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.SimpleSmoothingToolStripMenuItem.Text = "Simple Smoothing"
        '
        'NeonToolStripMenuItem
        '
        Me.NeonToolStripMenuItem.Name = "NeonToolStripMenuItem"
        Me.NeonToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.NeonToolStripMenuItem.Text = "Neon"
        '
        'HelpToolStripMenuItem
        '
        Me.HelpToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.PUIPHelpToolStripMenuItem, Me.AboutPUIPToolStripMenuItem})
        Me.HelpToolStripMenuItem.Name = "HelpToolStripMenuItem"
        Me.HelpToolStripMenuItem.Size = New System.Drawing.Size(44, 20)
        Me.HelpToolStripMenuItem.Text = "Help"
        '
        'PUIPHelpToolStripMenuItem
        '
        Me.PUIPHelpToolStripMenuItem.Name = "PUIPHelpToolStripMenuItem"
        Me.PUIPHelpToolStripMenuItem.Size = New System.Drawing.Size(135, 22)
        Me.PUIPHelpToolStripMenuItem.Text = "PUIP help"
        '
        'AboutPUIPToolStripMenuItem
        '
        Me.AboutPUIPToolStripMenuItem.Name = "AboutPUIPToolStripMenuItem"
        Me.AboutPUIPToolStripMenuItem.Size = New System.Drawing.Size(135, 22)
        Me.AboutPUIPToolStripMenuItem.Text = "About PUIP"
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'PicImage
        '
        Me.PicImage.Location = New System.Drawing.Point(12, 49)
        Me.PicImage.Name = "PicImage"
        Me.PicImage.Size = New System.Drawing.Size(574, 477)
        Me.PicImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.PicImage.TabIndex = 1
        Me.PicImage.TabStop = False
        '
        'ContextMenuStrip1
        '
        Me.ContextMenuStrip1.Name = "ContextMenuStrip1"
        Me.ContextMenuStrip1.Size = New System.Drawing.Size(61, 4)
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(12, 20)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(45, 23)
        Me.Button1.TabIndex = 3
        Me.Button1.Text = "Zoom"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'ToolStrip1
        '
        Me.ToolStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.Zoom1Tool, Me.Zoom})
        Me.ToolStrip1.Location = New System.Drawing.Point(0, 24)
        Me.ToolStrip1.Name = "ToolStrip1"
        Me.ToolStrip1.Size = New System.Drawing.Size(981, 25)
        Me.ToolStrip1.TabIndex = 4
        Me.ToolStrip1.Text = "Tools"
        '
        'Zoom1Tool
        '
        Me.Zoom1Tool.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.Zoom1Tool.Image = CType(resources.GetObject("Zoom1Tool.Image"), System.Drawing.Image)
        Me.Zoom1Tool.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.Zoom1Tool.Name = "Zoom1Tool"
        Me.Zoom1Tool.Size = New System.Drawing.Size(23, 22)
        Me.Zoom1Tool.Text = "Zoom 100%"
        '
        'Zoom
        '
        Me.Zoom.DropDownWidth = 75
        Me.Zoom.Name = "Zoom"
        Me.Zoom.Size = New System.Drawing.Size(75, 25)
        Me.Zoom.Text = "100%"
        '
        'Panel1
        '
        Me.Panel1.BackColor = System.Drawing.Color.FromArgb(CType(CType(255, Byte), Integer), CType(CType(224, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.Panel1.Location = New System.Drawing.Point(630, 76)
        Me.Panel1.Name = "Panel1"
        Me.Panel1.Size = New System.Drawing.Size(256, 148)
        Me.Panel1.TabIndex = 5
        '
        'Panel2
        '
        Me.Panel2.BackColor = System.Drawing.Color.FromArgb(CType(CType(255, Byte), Integer), CType(CType(224, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.Panel2.Location = New System.Drawing.Point(630, 230)
        Me.Panel2.Name = "Panel2"
        Me.Panel2.Size = New System.Drawing.Size(256, 136)
        Me.Panel2.TabIndex = 6
        '
        'Panel3
        '
        Me.Panel3.BackColor = System.Drawing.Color.FromArgb(CType(CType(255, Byte), Integer), CType(CType(224, Byte), Integer), CType(CType(192, Byte), Integer))
        Me.Panel3.Location = New System.Drawing.Point(630, 372)
        Me.Panel3.Name = "Panel3"
        Me.Panel3.Size = New System.Drawing.Size(256, 154)
        Me.Panel3.TabIndex = 7
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(630, 49)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(115, 16)
        Me.Label1.TabIndex = 8
        Me.Label1.Text = "Histogram RGB"
        '
        'ProgressBar1
        '
        Me.ProgressBar1.Location = New System.Drawing.Point(13, 547)
        Me.ProgressBar1.Name = "ProgressBar1"
        Me.ProgressBar1.Size = New System.Drawing.Size(573, 23)
        Me.ProgressBar1.TabIndex = 9
        '
        'SharpenToolStripMenuItem
        '
        Me.SharpenToolStripMenuItem.Name = "SharpenToolStripMenuItem"
        Me.SharpenToolStripMenuItem.Size = New System.Drawing.Size(197, 22)
        Me.SharpenToolStripMenuItem.Text = "Sharpen"
        '
        'MainForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(981, 597)
        Me.Controls.Add(Me.ProgressBar1)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Panel3)
        Me.Controls.Add(Me.Panel2)
        Me.Controls.Add(Me.Panel1)
        Me.Controls.Add(Me.ToolStrip1)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.PicImage)
        Me.Controls.Add(Me.MenuStrip1)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "MainForm"
        Me.Text = " "
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        CType(Me.PicImage, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ToolStrip1.ResumeLayout(False)
        Me.ToolStrip1.PerformLayout()
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
    Friend WithEvents CopyToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents PasteToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ZoomToFitToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ZoomToInToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ZoomToOutToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents PUIPHelpToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents AboutPUIPToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ContextMenuStrip1 As System.Windows.Forms.ContextMenuStrip
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents ToolStrip1 As System.Windows.Forms.ToolStrip
    Friend WithEvents Zoom1Tool As System.Windows.Forms.ToolStripButton
    Friend WithEvents Zoom As ToolStripComboBox
    Friend WithEvents RightRotateToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents LeftRotateToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ColorDialog1 As ColorDialog
    Friend WithEvents NeighborhoodFilterToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents MeanFilterToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents MedianFilterToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents VerticleToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents Panel1 As Panel
    Friend WithEvents Panel2 As Panel
    Friend WithEvents Panel3 As Panel
    Friend WithEvents Label1 As Label
    Friend WithEvents BrightenssToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents NegationToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ProgressBar1 As ProgressBar
    Friend WithEvents GrayShadeToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents HistogramBalanceToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AutoContrastToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AverageFilterToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ColorContrastToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SimpleSmoothingToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents NeonToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SharpenToolStripMenuItem As ToolStripMenuItem
End Class
