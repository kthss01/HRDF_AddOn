using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class csButton : MonoBehaviour {
    GameObject obj;
    Text txt;
    List<string> list;
    int index = 0;

    // Use this for initialization
    void Start () {
        list = GameObject.Find("Manager").GetComponent<DB>().list;
        obj = GameObject.Find("Output");
        txt = obj.GetComponent<Text>();
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void ChangeText()
    {
        txt.text = list[index++];
    }
}
