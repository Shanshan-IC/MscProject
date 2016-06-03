Public Class Brightness


    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK

        Dim mapclone As Bitmap = MainForm.bitmaps.Clone
        Dim r, g, b, j As Integer
        MainForm.ProgressBar1.Value = 0
        MainForm.ProgressBar1.Maximum = MainForm.bitmaps.Height

        Dim hist(255) As Integer
        j = TrackBar1.Value

        For i As Integer = 0 To 255
            hist(i) = i + j

            If hist(i) > 225 Then
                hist(i) = 225
            End If
            If hist(i) < 0 Then
                hist(i) = 0
            End If
        Next

        For y As Integer = 0 To mapclone.Height - 1
            For x As Integer = 0 To mapclone.Width - 1
                r = mapclone.GetPixel(x, y).R
                g = mapclone.GetPixel(x, y).G
                b = mapclone.GetPixel(x, y).B

                mapclone.SetPixel(x, y, Color.FromArgb(hist(r), hist(g), hist(b)))
            Next
            MainForm.ProgressBar1.Value = MainForm.ProgressBar1.Value + 1
        Next
        MainForm.PicImage.Image = mapclone
        MainForm.PicImage.Refresh()
        Me.Close()

        bitmap_hist()
        MainForm.Refresh()
    End Sub


    Sub bitmap_hist()

        Dim histR(255), histB(255), histG(255) As Integer

        Dim pic As Bitmap = MainForm.PicImage.Image
        Dim pic1 As Bitmap = New Bitmap(pic.Width, pic.Height)
        Dim R, G, B As Integer

        For i As Integer = 0 To 255
            histR(i) = 0
            histG(i) = 0
            histB(i) = 0
        Next

        For x As Integer = 0 To MainForm.PicImage.Image.Width - 1
            For y As Integer = 0 To MainForm.PicImage.Image.Height - 1
                R = pic.GetPixel(x, y).R
                G = pic.GetPixel(x, y).G
                B = pic.GetPixel(x, y).B
                histR(R) = histR(R) + 1
                histG(G) = histG(G) + 1
                histB(B) = histB(B) + 1
            Next
        Next

    End Sub

End Class