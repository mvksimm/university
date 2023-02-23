using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ValueConverter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "1";
            comboBox1.SelectedIndex = 0;
        }
        
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            comboBox2.Items.Clear();
            comboBox3.Items.Clear();
            string cb1 = comboBox1.SelectedItem.ToString();
            switch (cb1)
            {
                case "Валюта":
                    string[] value1 = {
                    "Рубль",
                    "Доллар",
                    "Евро",
                    "Иена",
                    "Динар"
                };
                    comboBox3.Items.AddRange(value1);
                    comboBox2.Items.AddRange(value1);
                    break;
                case "Объем":
                    string[] value2 = {
                    "Литр",
                    "Куб. метры",
                    "Стаканы",
                    "Куб. футы",
                    "Галлон"
                };
                    comboBox3.Items.AddRange(value2);
                    comboBox2.Items.AddRange(value2);
                    break;
                case "Масса и вес":
                    string[] value3 = {
                    "Грамм",
                    "Фунт",
                    "Килограмм",
                    "Миллиграмм",
                    "Карат"
                };
                    comboBox3.Items.AddRange(value3);
                    comboBox2.Items.AddRange(value3);
                    break;
                case "Длинна":
                    string[] value4 = {
                    "Метр",
                    "Дюйм",
                    "Миля",
                    "Фут",
                    "Ярды"
                };
                    comboBox3.Items.AddRange(value4);
                    comboBox2.Items.AddRange(value4);
                    break;
                case "Температура":
                    string[] value5 = {
                    "Цельсии",
                    "Фаренгейты",
                    "Кельвины"
                };
                    comboBox3.Items.AddRange(value5);
                    comboBox2.Items.AddRange(value5);
                    break;
                default:
                    break;
            }
            comboBox3.Items.Add("Всё сразу");
            comboBox2.SelectedIndex = 0;
            comboBox3.SelectedIndex = comboBox3.Items.Count - 1;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex == -1 || comboBox2.SelectedIndex == -1 || comboBox3.SelectedIndex == -1)
                return;
            double a, b = 0;
            try
            {
                a = Convert.ToDouble(textBox1.Text);
            }
            catch
            {
                a = 0;
                textBox1.Text = a.ToString();
            }
            
            string cb1 = comboBox1.SelectedItem.ToString();
            string cb2 = comboBox2.SelectedItem.ToString();
            string cb3 = comboBox3.SelectedItem.ToString();
            switch (cb1)
            {
                case "Валюта":
                    
                    var toRub = new Dictionary<string, double>()
                    {
                        { "Рубль", 1 },
                        { "Доллар", 76.1867 },
                        { "Евро", 86.8918 },
                        { "Иена", 0.6658 },
                        { "Динар", 0.05224}
                    };
                    var fromRub = new Dictionary<string, double>()
                    {
                        { "Рубль", 1 },
                        { "Доллар", 0.01313 },
                        { "Евро", 0.01151 },
                        { "Иена", 1.502 },
                        { "Динар", 19.1438}
                    };
                    if (cb3 == "Всё сразу")
                    {
                        textBox2.Text = "";
                        foreach (var i in fromRub)
                        {
                            textBox2.Text += $"{i.Key}: {Math.Round(a * toRub[cb2] * i.Value, 3)}\r\n"; 
                        }
                        return;
                    }

                    b = a * toRub[cb2] * fromRub[cb3];
                    break;
                case "Объем":
                    var toLitr = new Dictionary<string, double>()
                    {
                        { "Литр", 1 },
                        { "Куб. метры", 1000 },
                        { "Стаканы", 0.236588 },
                        { "Куб. футы", 28.31685 },
                        { "Галлон", 6.22835}
                    };
                    var fromLitr = new Dictionary<string, double>()
                    {
                        { "Литр", 1 },
                        { "Куб. метры", 0.001 },
                        { "Стаканы", 4.226753 },
                        { "Куб. футы", 0.035315 },
                        { "Галлон", 6.22835}
                    };
                    if (cb3 == "Всё сразу")
                    {
                        textBox2.Text = "";
                        foreach (var i in fromLitr)
                        {
                            textBox2.Text += $"{i.Key}: {Math.Round(a * toLitr[cb2] * i.Value, 3)}\r\n";
                        }
                        return;
                    }
                    b = a * toLitr[cb2] * fromLitr[cb3];
                    break;
                case "Масса и вес":
                    var toGramm = new Dictionary<string, double>()
                    {
                        { "Грамм", 1 },
                        { "Фунт", 453.5924 },
                        { "Килограмм", 1000 },
                        { "Миллиграмм", 0.001 },
                        { "Карат", 0.2}
                    };
                    var fromGramm = new Dictionary<string, double>()
                    {
                        { "Грамм", 1 },
                        { "Фунт", 0.002205 },
                        { "Килограмм", 0.001 },
                        { "Миллиграмм", 1000 },
                        { "Карат", 5}
                    };
                    if (cb3 == "Всё сразу")
                    {
                        textBox2.Text = "";
                        foreach (var i in fromGramm)
                        {
                            textBox2.Text += $"{i.Key}: {Math.Round(a * toGramm[cb2] * i.Value, 5)}\r\n";
                        }
                        return;
                    }
                    b = a * toGramm[cb2] * fromGramm[cb3];
                    break;
                case "Длинна":
                    var toMetr = new Dictionary<string, double>()
                    {
                        { "Метр", 1 },
                        { "Дюйм", 0.0254 },
                        { "Миля", 1609.344 },
                        { "Фут", 0.3048 },
                        { "Ярды", 0.9144 }
                    };
                    var fromMetr = new Dictionary<string, double>()
                    {
                        { "Метр", 1 },
                        { "Дюйм", 0.0254 },
                        { "Миля", 1609.344 },
                        { "Фут", 0.3048 },
                        { "Ярды", 0.9144 }
                    };
                    if (cb3 == "Всё сразу")
                    {
                        textBox2.Text = "";
                        foreach (var i in fromMetr)
                        {
                            textBox2.Text += $"{i.Key}: {Math.Round(a * toMetr[cb2] * i.Value, 5)}\r\n";
                        }
                        return;
                    }
                    b = a * fromMetr[cb3] * toMetr[cb2];
                    break;
                case "Температура":
                    switch (cb2)
                    {
                        case "Цельсии":
                            switch (cb3)
                            {
                                case "Цельсии":
                                    b = a;
                                    break;
                                case "Фаренгейты":
                                    b = (a * 9 / 5) + 32;
                                    break;
                                case "Кельвины":
                                    b = a + 273;
                                    break;
                                case "Всё сразу":
                                    textBox2.Text = $"Цельсии: {a}\r\nФаренгейты: {(a * 9 / 5) + 32}\r\nКельвины: {a + 273}";
                                    return;
                            }
                            break;
                        case "Фаренгейты":
                            switch (cb3)
                            {
                                case "Цельсии":
                                    b = (a - 32) * 5 / 9;
                                    break;
                                case "Фаренгейты":
                                    b = a;
                                    break;
                                case "Кельвины":
                                    b = (a - 32) * 5 / 9 + 273;
                                    break;
                                case "Всё сразу":
                                    textBox2.Text = $"Цельсии: {(a - 32) * 5 / 9}\r\nФаренгейты: {a}\r\nКельвины: {(a - 32) * 5 / 9 + 273}";
                                    return;
                            }
                            break;
                        case "Кельвины":
                            switch (cb3)
                            {
                                case "Цельсии":
                                    b = a - 273;
                                    break;
                                case "Фаренгейты":
                                    b = a;
                                    break;
                                case "Кельвины":
                                    b = (a - 273) * 9 / 5 + 32;
                                    break;
                                case "Всё сразу":
                                    textBox2.Text = $"Цельсии: {a-273}\r\nФаренгейты: {a}\r\nКельвины: {(a - 273) * 9 / 5 + 32}";
                                    return;
                            }
                            break;
                    }
                    break;
                default:
                    break;
            }
            textBox2.Text = b.ToString();
        }
    }
}
