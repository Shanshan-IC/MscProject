<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class RGB
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
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
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.rgbImage = New System.Windows.Forms.PictureBox()
        Me.Rpicture = New System.Windows.Forms.PictureBox()
        Me.Gpicture = New System.Windows.Forms.PictureBox()
        Me.Bpicture = New System.Windows.Forms.PictureBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        CType(Me.rgbImage, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.Rpicture, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.Gpicture, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.Bpicture, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'rgbImage
        '
        Me.rgbImage.Location = New System.Drawing.Point(24, 42)
        Me.rgbImage.Name = "rgbImage"
        Me.rgbImage.Size = New System.Drawing.Size(360, 237)
        Me.rgbImage.TabIndex = 0
        Me.rgbImage.TabStop = False
        '
        'Rpicture
        '
        Me.Rpicture.Location = New System.Drawing.Point(434, 42)
        Me.Rpicture.Name = "Rpicture"
        Me.Rpicture.Size = New System.Drawing.Size(360, 237)
        Me.Rpicture.TabIndex = 3
        Me.Rpicture.TabStop = False
        '
        'Gpicture
        '
        Me.Gpicture.Location = New System.Drawing.Point(24, 351)
        Me.Gpicture.Name = "Gpicture"
        Me.Gpicture.Size = New System.Drawing.Size(360, 237)
        Me.Gpicture.TabIndex = 4
        Me.Gpicture.TabStop = False
        '
        'Bpicture
        '
        Me.Bpicture.Location = New System.Drawing.Point(434, 351)
        Me.Bpicture.Name = "Bpicture"
        Me.Bpicture.Size = New System.Drawing.Size(360, 237)
        Me.Bpicture.TabIndex = 5
        Me.Bpicture.TabStop = False
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(151, 14)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(74, 13)
        Me.Label1.TabIndex = 10
        Me.Label1.Text = "Original Image"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(545, 14)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(47, 13)
        Me.Label2.TabIndex = 11
        Me.Label2.Text = "R Image"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(151, 316)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(47, 13)
        Me.Label3.TabIndex = 12
        Me.Label3.Text = "G Image"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(545, 316)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(46, 13)
        Me.Label4.TabIndex = 13
        Me.Label4.Text = "B Image"
        '
        'RGB
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(834, 609)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Bpicture)
        Me.Controls.Add(Me.Gpicture)
        Me.Controls.Add(Me.Rpicture)
        Me.Controls.Add(Me.rgbImage)
        Me.Name = "RGB"
        Me.Text = "RGB"
        CType(Me.rgbImage, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.Rpicture, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.Gpicture, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.Bpicture, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents rgbImage As PictureBox
    Friend WithEvents Rpicture As PictureBox
    Friend WithEvents Gpicture As PictureBox
    Friend WithEvents Bpicture As PictureBox
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents Label4 As Label
End Class
