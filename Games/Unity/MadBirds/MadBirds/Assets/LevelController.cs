using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelController : MonoBehaviour
{
    private static int _nextLevelIndex = 1;
    private Enemy[] _enemies;

    private void OnEnable()
    {
        _enemies = FindObjectsOfType<Enemy>();
    }

    private void Update()
    {
        foreach (Enemy enemy in _enemies)
        {
            if (enemy)
            {
                return;
            }
        }
        if (_enemies.Length > 0)
        {
            Debug.Log("You killed all enemies");
        }
        _nextLevelIndex++;
        string nextLevelName = "Level" + _nextLevelIndex;
        SceneManager.LoadScene(nextLevelName);
    }

}
