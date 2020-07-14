using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.Xml.Linq;
using System.Collections.ObjectModel;
using System.IO;

namespace FinalProject_18300021
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        public int count = 0;
        public int loopCount = 0;
        public string[] filePath = new string[5];
        ObservableCollection<ItemClass> ViewCollection = new ObservableCollection<ItemClass>();

        public MainWindow()
        {
            InitializeComponent();
            DataGridBox.DataContext = ViewCollection;
        }

        private void LoadPathButton_Click(object sender, RoutedEventArgs e)
        {
            FolderBrowserDialog fd = new FolderBrowserDialog();
            fd.Description = "フォルダーを選択してください";
            if(fd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                ViewCollection.Clear();
                ImportPathBox.Text = fd.SelectedPath;
                filePath[0] = ImportPathBox.Text;
                AddCollection(filePath, loopCount);
            }
            
        }

        public void AddCollection(string[] filePath,int loopCount)
        {

            var paths = System.IO.Directory.GetFileSystemEntries(filePath[loopCount]).Select(x => System.IO.Path.GetFileName(x)).ToArray();

            foreach (var path in paths)
            {

                ItemClass item = new ItemClass();
                item.NO = ++count;

                switch (loopCount)
                {
                    case 0:
                        item.FIELD1 = path.ToString();
                        break;
                    case 1:
                        item.FIELD2 = path.ToString();
                        break;
                    case 2:
                        item.FIELD3 = path.ToString();
                        break;
                    case 3:
                        item.FIELD4 = path.ToString();
                        break;
                    case 4:
                        item.FIELD5 = path.ToString();
                        break;
                }
                item.SELFMADE = 0;
                item.EXTENSION = System.IO.Path.GetExtension(filePath + @"\" + path.ToString());

                ViewCollection.Add(item);
                if (loopCount < 4)
                {
                    filePath[loopCount + 1] = filePath[loopCount] + @"\" + path.ToString();
                    if (System.IO.Directory.Exists(filePath[loopCount + 1]))
                    {
                        loopCount++;
                        AddCollection(filePath, loopCount);
                        loopCount--;
                    }
                }
            }
           
        }

        private void ExportButton_Click(object sender, RoutedEventArgs e)
        {
            //SaveFileDialogクラスのインスタンスを作成
            SaveFileDialog sfd = new SaveFileDialog();

            sfd.FileName = "新しいファイル.txt";
            sfd.InitialDirectory = filePath[0];
            sfd.Filter = "HTMLファイル(*.html;*.htm)|*.html;*.htm|すべてのファイル(*.*)|*.*|テキストファイル(*.txt)|*.txt";
            sfd.FilterIndex = 3;
            sfd.Title = "保存先のファイルを選択してください";
            sfd.RestoreDirectory = true;
            sfd.OverwritePrompt = true;
            sfd.CheckPathExists = true;

            //ダイアログを表示する
            if (sfd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                System.IO.StreamWriter sw = new System.IO.StreamWriter(sfd.FileName);
                foreach(var data in ViewCollection)
                {
                    string output = "";

                    if (data.FIELD1 != null)
                        output += ("\n" + data.FIELD1.ToString());
                    if (data.FIELD2 != null)
                        output += ("  L " + data.FIELD2.ToString());
                    if (data.FIELD3 != null)
                        output += ("      L " + data.FIELD3.ToString());
                    if (data.FIELD4 != null)
                        output += ("          L " + data.FIELD4.ToString());
                    if (data.FIELD5 != null)
                        output += ("              L " + data.FIELD5.ToString());
                    switch (data.SELFMADE)
                    {
                        case 0:
                            break;
                        case 1:
                            output += "     〇一部担当";
                            break;
                        case 2:
                            output += "     ●担当箇所";
                            break;
                    }

                    sw.WriteLine(output);
                }
                sw.Close();
            }
        }

        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {

        }
    }
}
