package sk.magiksoft.intellihome;

import android.app.Activity;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

/**
 * User: wladimiiir
 * Date: 5/14/14
 * Time: 8:23 PM
 */
public class Settings extends Activity {
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.settings);
        getActionBar().setDisplayHomeAsUpEnabled(true);

        final Spinner defaultServerList = (Spinner) findViewById(R.id.defaultServerList);
        defaultServerList.setAdapter(new ArrayAdapter<String>(this, R.layout.server_address, Constants.DEFAULT_SERVERS));
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                finish();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }
}