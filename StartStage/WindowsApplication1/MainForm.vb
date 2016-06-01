Public Class MainForm
    Public WithEvents mImage As New ImageClass

    Private Sub FileToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FileToolStripMenuItem.Click

    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub OpenAnImageToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles OpenAnImageToolStripMenuItem.Click
        If Me.OpenFileDialog1.ShowDialog = Windows.Forms.DialogResult.OK Then
            Dim FName As String = Me.OpenFileDialog1.FileName
            Me.PicImage.ImageLocation = FName
        End If

    End Sub

    Private Sub MenuStrip1_ItemClicked(sender As Object, e As ToolStripItemClickedEventArgs) Handles MenuStrip1.ItemClicked

    End Sub

    Private Sub PictureBox1_Click(sender As Object, e As EventArgs) Handles PicImage.Click

    End Sub

    Private Sub SaveToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SaveToolStripMenuItem.Click

        SaveImage.ShowDialog()

        If SaveImage.FileName > "" Then
            PicImage.Image.Save(SaveImage.FileName)

        End If

    End Sub

    Private Sub ExitToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ExitToolStripMenuItem.Click

        End

    End Sub

    Private Sub UndoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles UndoToolStripMenuItem.Click

    End Sub

    Private Sub AboutPUIPToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AboutPUIPToolStripMenuItem.Click
        MsgBox("ZAMN Editor Beta v 1.1 & Environment.NewLine" & "Recources could be gained from https: //github.com/Shanshan-IC/MscProject" & Environment.NewLine & Environment.NewLine & "Copyright © 2016 ShanshanFu", MsgBoxStyle.Information, "About")
    End Sub


    Private Sub PUIPHelpToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PUIPHelpToolStripMenuItem.Click

    End Sub


    Private Sub ZoomToInToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomToInToolStripMenuItem.Click
        Me.PicImage.Width += 20%
        Me.PicImage.Height += 20%

    End Sub

    Private Sub Zoom1Tool_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click

    End Sub

    Private Sub Zoom_Click(sender As Object, e As EventArgs) Handles Zoom.Click

    End Sub

    Private Sub ZoomToFitToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomToFitToolStripMenuItem.Click

    End Sub

    Private Sub ZoomToOutToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomToOutToolStripMenuItem.Click
        Me.PicImage.Width -= 20%
        Me.PicImage.Height -= 20%
    End Sub

    Private Sub RightRotateToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RightRotateToolStripMenuItem.Click

        Dim w As Integer = Me.PicImage.Width
        Dim h As Integer = Me.PicImage.Height

        Me.PicImage.Image.RotateFlip(RotateFlipType.Rotate90FlipNone)
        Me.PicImage.Height = h
        Me.PicImage.Width = w

        Me.PicImage.Refresh()
        'Me.PicImage.Image.RotateFlip(RotateFlipType.Rotate90FlipNone)
        'Me.PicImage.Refresh()
    End Sub

    Private Sub LeftRotateToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LeftRotateToolStripMenuItem.Click
        Dim w As Integer = Me.PicImage.Width
        Dim h As Integer = Me.PicImage.Height

        Me.PicImage.Image.RotateFlip(RotateFlipType.Rotate90FlipXY)
        Me.PicImage.Height = h
        Me.PicImage.Width = w
        Me.PicImage.Refresh()

    End Sub

    Private Sub GridToolStripMenuItem_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub AnalysisToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AnalysisToolStripMenuItem.Click

    End Sub

    Private Sub MeanFilterToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles MeanFilterToolStripMenuItem.Click
        mImage.meanfilter(3, True)
    End Sub
End Class
