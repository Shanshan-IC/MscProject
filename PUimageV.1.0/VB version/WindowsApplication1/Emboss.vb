Public Class Emboss
    Private Sub Label1_Click(sender As Object, e As EventArgs) Handles Label1.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Dim dlg As New SaveFileDialog

        dlg.Filter = "PNG Files (.png)|*.png|BMP Files (.bmp)|*.bmp|JPEG Files (.jpg)|*.jpg"
        dlg.FilterIndex = 1
        dlg.RestoreDirectory = True

        If dlg.ShowDialog() = DialogResult.OK Then
            If Len(dlg.FileName) = 0 Then Exit Sub

            Select Case dlg.FilterIndex
                Case 1
                    EmbossImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Png)
                Case 2
                    EmbossImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Bmp)
                Case 3
                    EmbossImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Jpeg)
            End Select
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK

        Dim mapclone As Bitmap = MainForm.bitmaps.Clone
        Dim r, g, b, r2, g2, b2, rr, gg, bb, j As Integer

        j = TrackBar1.Value

        For y As Integer = 0 To mapclone.Height - 2
            For x As Integer = 0 To mapclone.Width - 2
                r = mapclone.GetPixel(x, y).R
                g = mapclone.GetPixel(x, y).G
                b = mapclone.GetPixel(x, y).B

                r2 = mapclone.GetPixel(x + 1, y + 1).R
                g2 = mapclone.GetPixel(x + 1, y + 1).G
                b2 = mapclone.GetPixel(x + 1, y + 1).B

                rr = (r - r2) * j + 128
                gg = (g - g2) * j + 128
                bb = (b - b2) * j + 128

                If rr < 0 Then rr = 0
                If rr > 255 Then rr = 255
                If gg < 0 Then gg = 0
                If gg > 255 Then gg = 255
                If bb < 0 Then bb = 0
                If bb > 255 Then bb = 255

                mapclone.SetPixel(x, y, Color.FromArgb(rr, gg, bb))
            Next
        Next
        EmbossImage.Image = mapclone
        EmbossImage.Refresh()

    End Sub
End Class