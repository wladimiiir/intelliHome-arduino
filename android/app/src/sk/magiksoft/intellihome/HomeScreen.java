package sk.magiksoft.intellihome;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

/**
 * User: wladimiiir
 * Date: 4/8/14
 * Time: 7:32 PM
 */
public class HomeScreen extends Activity {
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.home_screen);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.home_screen_menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onMenuItemSelected(int featureId, MenuItem item) {
        switch (item.getItemId()) {
            case R.id.settings:
                showSettings();
                break;
        }
        return super.onMenuItemSelected(featureId, item);
    }

    private void showSettings() {
        startActivity(new Intent(this, Settings.class));
    }

    public void showMyHome(View view) {
        startActivity(new Intent(this, MyHomeInfo.class));
    }

    public void showConfiguration(View view) {
        startActivity(new Intent(this, ConfigPage.class));
    }

    public void exit(View view) {
        finish();
    }

}