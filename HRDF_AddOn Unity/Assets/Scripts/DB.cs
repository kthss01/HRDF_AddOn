using UnityEngine;
using System.Collections;
using System.IO;

public class DB : MonoBehaviour {

	// Use this for initialization
	void Start () {
        Read();
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
            Debug.Log(s);
        }
        sr.Close();
    }
}
