Public Class ColorBoard
    Public aa, rr, gg, bb, nr, ng, nb As Integer
    Public originmap As Bitmap

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim dlg As New SaveFileDialog

        dlg.Filter = "PNG Files (.png)|*.png|BMP Files (.bmp)|*.bmp|JPEG Files (.jpg)|*.jpg"
        dlg.FilterIndex = 1
        dlg.RestoreDirectory = True

        If dlg.ShowDialog() = DialogResult.OK Then
            If Len(dlg.FileName) = 0 Then Exit Sub

            Select Case dlg.FilterIndex
                Case 1
                    ColorImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Png)
                Case 2
                    ColorImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Bmp)
                Case 3
                    ColorImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Jpeg)
            End Select
        End If

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        ColorImage.Image = originmap

    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Me.Close()
    End Sub

    Private Sub ColorBoard_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim pic As Bitmap = ColorImage.Image
        originmap = ColorImage.Image
    End Sub

    Private Sub changecolor()
        RText.Text = Rbar.Value
        GText.Text = Gbar.Value
        BText.Text = Bbar.Value
        Dim pic As Bitmap = ColorImage.Image

        For y As Integer = 0 To ColorImage.Image.Height - 1
            For x As Integer = 0 To ColorImage.Image.Width - 1
                aa = pic.GetPixel(x, y).A
                rr = pic.GetPixel(x, y).R
                gg = pic.GetPixel(x, y).G
                bb = pic.GetPixel(x, y).B
                nr = rr + Rbar.Value
                ng = gg + Gbar.Value
                nb = bb + Bbar.Value

                If nr < 0 Then nr = 0
                If nr > 255 Then nr = 255
                If ng < 0 Then ng = 0
                If ng > 255 Then ng = 255
                If nb < 0 Then nb = 0
                If nb > 255 Then nb = 255

                pic.SetPixel(x, y, Color.FromArgb(aa, nr, ng, nb))
            Next
        Next
        ColorImage.Image = pic
    End Sub

    Private Sub Rbar_Scroll(sender As Object, e As EventArgs) Handles Rbar.Scroll
        changecolor()
    End Sub

    Private Sub Gbar_Scroll(sender As Object, e As EventArgs) Handles Gbar.Scroll
        changecolor()
    End Sub

    Private Sub Bbar_Scroll(sender As Object, e As EventArgs) Handles Bbar.Scroll
        changecolor()
    End Sub
End Class