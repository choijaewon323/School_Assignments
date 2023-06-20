package execution;

import java.awt.*;
import java.awt.event.*;
import java.util.Calendar;

import javax.swing.*;
import javax.swing.event.*;

import calendar.MyCalendar;

public class MyGUIProject extends JFrame {
	
	Container container = getContentPane();
	
	MyModalDialog dialog;
	
	public static String[][][] memos;
	
	JPanel panel1 = new JPanel();
	JPanel panel2 = new JPanel();
	
	JButton before = new JButton("Before");
	JButton after = new JButton("After");
	
	JLabel day = new JLabel("0000/00");
	String[] days = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
	
	JButton[] buttons = new JButton[42];
	
	calendar.MyCalendar myCalendar = new MyCalendar();
	
	public MyGUIProject() {
		
		setTitle("My calendar & To do");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		MyActionPerformed myActionPerformed = new MyActionPerformed();
		before.addActionListener(myActionPerformed);
		after.addActionListener(myActionPerformed);
		
		dialog = new MyModalDialog(this, "Todo");
		
		init();
		
		setSize(500, 500);
		setVisible(true);
		
	}
	
	private void init() {
		
		memos = new String[3001][13][32];
		
		container.setLayout(new BorderLayout());
		panel1.setBackground(Color.WHITE);
		panel2.setBackground(Color.WHITE);
		container.add(panel1, BorderLayout.NORTH);
		container.add(panel2, BorderLayout.CENTER);
		
		panel1.setLayout(new FlowLayout());
		panel1.add(before);
		panel1.add(day);
		panel1.add(after);
		
		day.setText(myCalendar.getDay());
		
		panel2.setLayout(new GridLayout(0, 7));
		
		// sun, mon ... setting
		for (int i = 0; i < 7; i++) {
			JLabel temp = new JLabel(days[i], SwingConstants.CENTER);
			
			if (i == 0) {
				temp.setBackground(Color.RED);
			} else if (i == 6) {
				temp.setBackground(Color.BLUE);
			} else {
				temp.setBackground(Color.GRAY);
			}
			
			temp.setForeground(Color.WHITE);
			temp.setOpaque(true);
			
			panel2.add(temp);
		}
		
		for (int i = 0; i < 42; i++) {
			buttons[i] = new JButton();
			
			buttons[i].addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					
					int year = myCalendar.getYear();
					int month = myCalendar.getMonth();
					int day = Integer.parseInt(((JButton)(e.getSource())).getText());
					
					dialog.setText(memos[year][month][day]);
					dialog.setDay(year + "/" + month + "/" + day);
					
					dialog.setVisible(true);
					
					String result = dialog.getInput();
					
					if (result != null) {
						((JButton)e.getSource()).setForeground(Color.RED);
					} else {
						((JButton)e.getSource()).setForeground(Color.BLACK);
					}
					memos[year][month][day] = result;
				}
			});
			
			panel2.add(buttons[i]);
		}
		
		myCalendar.setButtons(buttons);
		myCalendar.setCalendar();
		
		
	}
	
	class MyActionPerformed implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			boolean prev = true;
			
			if (e.getSource() == before) {
				prev = true;
			} else if (e.getSource() == after) {
				prev = false;
			}
			
			myCalendar.renewal(prev);
			day.setText(myCalendar.getDay());
		}
		
	}
	
	class MyModalDialog extends JDialog {
		private JLabel day = new JLabel("", SwingConstants.CENTER);
		private JTextArea text = new JTextArea();
		private JButton done = new JButton("done");
		
		public MyModalDialog(JFrame frame, String title) {
			super(frame, title, true);
			setLayout(new BorderLayout());
			add(day, BorderLayout.NORTH);
			add(text, BorderLayout.CENTER);
			done.setBackground(Color.WHITE);
			add(done, BorderLayout.SOUTH);
			setSize(300, 300);
			
			done.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					setVisible(false);
				}
			});
		}
		
		public String getInput() {
			if (text.getText().length() == 0) {
				return null;
			} else {
				return text.getText();
			}
		}
		
		public void setText(String t) {
			text.setText(t);
		}
		
		public void setDay(String t) {
			day.setFont(new Font("SansSerif", Font.BOLD, 20));
			day.setText(t);
		}
	}
	
	public static void main(String[] args) {
		
		new MyGUIProject();
	
	}
	
}
