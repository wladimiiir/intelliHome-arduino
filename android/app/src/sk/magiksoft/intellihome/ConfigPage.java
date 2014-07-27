package sk.magiksoft.intellihome;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Xml;
import android.view.MenuItem;
import android.view.View;
import android.widget.RadioButton;
import android.widget.TextView;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * User: wladimiiir
 * Date: 4/9/14
 * Time: 9:22 PM
 */
public class ConfigPage extends Activity {
    private String serverIP;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.config_page);

        final SharedPreferences preferences = getApplicationContext().getSharedPreferences(Constants.SETTINGS_FILENAME, MODE_PRIVATE);
        serverIP = preferences.getString(Constants.KEY_SERVER_IP, Constants.DEFAULT_SERVERS[0]);
    }

    @Override
    protected void onStart() {
        super.onStart();
        loadConfigValues();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                final Intent intent = new Intent(this, HomeScreen.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                startActivity(intent);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private boolean isNetworkAvailable() {
        final ConnectivityManager connMgr = (ConnectivityManager)
                getSystemService(Context.CONNECTIVITY_SERVICE);
        final NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
        return networkInfo != null && networkInfo.isConnected();
    }

    private void loadConfigValues() {
        new LoadConfigTask().execute();
    }

    public void setManualTemperature(View view) {
        final TextView minTemp = (TextView) findViewById(R.id.bedroomMinTemp);
        final TextView maxTemp = (TextView) findViewById(R.id.bedroomMaxTemp);
        setValue("bedroomMinTemp", minTemp.getText().toString(), false);
        setValue("bedroomMaxTemp", maxTemp.getText().toString(), false);
    }

    public void setAutoTemperature(View view) {
        setValue("bedroomMinTemp", "Auto", true);
        setValue("bedroomMaxTemp", "Auto", true);
    }

    public void setElectricHeaterState(View view) {
        final RadioButton on = (RadioButton) findViewById(R.id.electricHeaterOn);
        final RadioButton off = (RadioButton) findViewById(R.id.electricHeaterOff);
        final RadioButton auto = (RadioButton) findViewById(R.id.electricHeaterAuto);

        if (on.isChecked()) {
            setValue("electricHeater", "On", false);
        } else if (off.isChecked()) {
            setValue("electricHeater", "Off", false);
        } else if (auto.isChecked()) {
            setValue("electricHeater", "Auto", false);
        }
    }

    private void setValue(String key, String value, final boolean reloadConfigValues) {
        new AsyncTask<String, Void, Void>() {
            @Override
            protected Void doInBackground(String... params) {
                if (isNetworkAvailable()) {
                    try {
                        final URL url = new URL("http://" + serverIP + ":776/set_config?" + params[0] + "=" + params[1]);
                        final HttpURLConnection connection = (HttpURLConnection) url.openConnection();

                        connection.setRequestMethod("GET");
                        connection.connect();
                        if (connection.getResponseCode() != 200) {
                            return null;
                        }
                        if (reloadConfigValues) {
                            loadConfigValues();
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } else {
                    // display error
                }
                return null;
            }
        }.execute(key, value);
    }

    public void increaseTemperature(View view) {
        final TextView minTemp = (TextView) findViewById(R.id.bedroomMinTemp);
        final TextView maxTemp = (TextView) findViewById(R.id.bedroomMaxTemp);

        try {
            Double minValue = Double.valueOf(minTemp.getText().toString());
            Double maxValue = Double.valueOf(maxTemp.getText().toString());

            minValue += 1;
            maxValue += 1;
            minTemp.setText(minValue.toString());
            maxTemp.setText(maxValue.toString());
        } catch (NumberFormatException e) {
            return;
        }
    }

    public void decreaseTemperature(View view) {
        final TextView minTemp = (TextView) findViewById(R.id.bedroomMinTemp);
        final TextView maxTemp = (TextView) findViewById(R.id.bedroomMaxTemp);

        try {
            Double minValue = Double.valueOf(minTemp.getText().toString());
            Double maxValue = Double.valueOf(maxTemp.getText().toString());

            minValue -= 1;
            maxValue -= 1;
            minTemp.setText(minValue.toString());
            maxTemp.setText(maxValue.toString());
        } catch (NumberFormatException e) {
            return;
        }
    }

    private class LoadConfigTask extends AsyncTask<Void, Void, Void> {
        @Override
        protected Void doInBackground(Void... params) {
            if (isNetworkAvailable()) {
                try {
                    loadConfigData();
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (XmlPullParserException e) {
                    e.printStackTrace();
                }
            } else {
                // display error
            }
            return null;
        }

        private void loadConfigData() throws IOException, XmlPullParserException {
            final URL url = new URL("http://" + serverIP + ":776/arduino_config_values");
            final HttpURLConnection connection = (HttpURLConnection) url.openConnection();

            connection.setRequestMethod("GET");
            connection.connect();
            if (connection.getResponseCode() != 200) {
                return;
            }

            InputStream inputStream = null;
            try {
                inputStream = connection.getInputStream();
                processConfigXml(inputStream);
            } finally {
                if (inputStream != null) {
                    inputStream.close();
                }
            }

        }

        private void processConfigXml(InputStream xmlContent) throws XmlPullParserException, IOException {
            final XmlPullParser parser = Xml.newPullParser();

            parser.setInput(xmlContent, "UTF-8");
            parser.setFeature(XmlPullParser.FEATURE_PROCESS_NAMESPACES, false);
            parser.nextTag();

            while (parser.next() != XmlPullParser.END_TAG) {
                if (parser.getEventType() != XmlPullParser.START_TAG) {
                    continue;
                }
                final String key = parser.getName();
                int id = getResources().getIdentifier(key, "id", "sk.magiksoft.intellihome");

                parser.next();
                final String text = parser.getText();

                if (id != 0) {
                    final View view = ConfigPage.this.findViewById(id);
                    if (view instanceof TextView) {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                ((TextView) view).setText(text);
                            }
                        });
                    }
                } else {
                    id = getResources().getIdentifier(key + text, "id", "sk.magiksoft.intellihome");
                    if (id != 0) {
                        final View view = ConfigPage.this.findViewById(id);
                        if (view instanceof RadioButton) {
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    ((RadioButton) view).setChecked(true);
                                }
                            });
                        }
                    }
                }
                parser.nextTag();
            }
        }
    }
}