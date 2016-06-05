Public Class Helper
    Private Sub TreeView1_AfterSelect(sender As Object, e As TreeViewEventArgs) Handles TreeView1.AfterSelect
        If e.Node.Name = "Node0" Then
            RichTextBox1.Text = " Hello world!"

        End If
    End Sub
End Class