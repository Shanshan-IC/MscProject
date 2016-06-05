Public Class RGB

    Public Rmaps, Bmaps, Gmaps As Bitmap

    Private Sub RGB_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim pic As Bitmap = rgbImage.Image
        Dim Rmaps As Bitmap = New Bitmap(pic.Width, pic.Height)
        Dim Bmaps As Bitmap = New Bitmap(pic.Width, pic.Height)
        Dim Gmaps As Bitmap = New Bitmap(pic.Width, pic.Height)
        For y As Integer = 0 To rgbImage.Image.Height - 1
            For x As Integer = 0 To rgbImage.Image.Width - 1
                a = pic.GetPixel(x, y).A
                r = pic.GetPixel(x, y).R
                g = pic.GetPixel(x, y).G
                b = pic.GetPixel(x, y).B

                Rmaps.SetPixel(x, y, Color.FromArgb(a, r, 0, 0))
                Gmaps.SetPixel(x, y, Color.FromArgb(a, 0, g, 0))
                Bmaps.SetPixel(x, y, Color.FromArgb(a, 0, 0, b))

            Next
        Next

        Rpicture.Image = Rmaps
        Gpicture.Image = Gmaps
        Bpicture.Image = Bmaps
    End Sub

    Public a, r, g, b As Integer

End Class