using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using System.IO;

public class DB : MonoBehaviour {
    public List<string> list = new List<string>();
    Text txt;

	// Use this for initialization
	void Start () {
        txt = GameObject.Find("Output").GetComponent<Text>();
        Read();
       // Print();
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void Read()
    {
        string path = @"C:\Users\김태훈\Documents\Unity Projects\HRDF_AddOn\Assets\db.txt";
        StreamReader sr = new StreamReader(path, System.Text.Encoding.Default);
        string s = "";
        while((s = sr.ReadLine()) != null)
        {
            list.Add(s);
        }
        sr.Close();
    }

    public void Print()
    {
        for(int i=0; i<list.Count; i++)
        {
            Debug.Log(list[i]);
        }
    }
}
