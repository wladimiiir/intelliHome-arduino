package sk.magiksoft.intellihome;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.*;
import android.util.Xml;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;

/**
 * User: wladimiiir
 * Date: 3/25/14
 * Time: 10:29 PM
 */
public class MyHomeInfo extends Activity {
    private static final int REFRESH_INTERVAL = 5000;
    private Handler handler;
    private Timer timer;
    private String serverIP;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                refresh();
            }
        };
        setContentView(R.layout.my_home_info);
        getActionBar().setDisplayHomeAsUpEnabled(true);

        final SharedPreferences preferences = getApplicationContext().getSharedPreferences(Constants.SETTINGS_FILENAME, MODE_PRIVATE);
        serverIP = preferences.getString(Constants.KEY_SERVER_IP, Constants.DEFAULT_SERVERS[0]);
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

    @Override
    protected void onResume() {
        timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                handler.obtainMessage(1).sendToTarget();
            }
        }, 0, REFRESH_INTERVAL);
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        timer.cancel();
        timer.purge();
    }

    private void refresh() {
        new RefreshDataTask().execute();
    }

    private class RefreshDataTask extends AsyncTask<Void, Void, Void> {
        @Override
        protected Void doInBackground(Void... params) {
            final ConnectivityManager connMgr = (ConnectivityManager)
                    getSystemService(Context.CONNECTIVITY_SERVICE);
            final NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
            if (networkInfo != null && networkInfo.isConnected()) {
                try {
                    refreshData();
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

        private void refreshData() throws IOException, XmlPullParserException {
            final URL url = new URL("http://" + serverIP + ":776/arduino_inputs");
            final HttpURLConnection connection = (HttpURLConnection) url.openConnection();

            connection.setRequestMethod("GET");
            connection.connect();
            if (connection.getResponseCode() != 200) {
                return;
            }

            InputStream inputStream = null;
            try {
                inputStream = connection.getInputStream();
                processInputsXml(inputStream);
            } finally {
                if (inputStream != null) {
                    inputStream.close();
                }
            }
        }

        private void processInputsXml(InputStream xmlContent) throws XmlPullParserException, IOException {
            final XmlPullParser parser = Xml.newPullParser();

            parser.setInput(xmlContent, "UTF-8");
            parser.setFeature(XmlPullParser.FEATURE_PROCESS_NAMESPACES, false);
            parser.nextTag();

            while (parser.next() != XmlPullParser.END_TAG) {
                if (parser.getEventType() != XmlPullParser.START_TAG) {
                    continue;
                }
                final String key = parser.getName();
                final int id = getResources().getIdentifier(key, "id", "sk.magiksoft.intellihome");
                if (id != 0) {
                    final View view = MyHomeInfo.this.findViewById(id);
                    if (view instanceof TextView) {
                        parser.next();
                        final String text = parser.getText();
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                ((TextView) view).setText(text);
                            }
                        });
                    }
                } else {
                    parser.next();
                }
                parser.nextTag();
            }
        }
    }
}